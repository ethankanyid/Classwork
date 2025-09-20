/************ t.c file ************/
#define NPROC 9
#define SSIZE 1024 /* kstack int size */

// Process status codes
#define FREE 0
#define READY 1
#define SLEEP 2
#define BLOCK 3
#define ZOMBIE 4

// Define null since it doesn't exist
#define NULL 0
#define null 0

// 1. PROC structure definition
typedef struct proc
{
    struct proc *next;
    int *ksp;            // saved sp when PROC is not running
    int status;          // FREE|READY|SLEEP|BLOCK|ZOMBIE
    int priority;        // scheduling priority
    int pid;             // process ID
    int ppid;            // parent process ID
    struct proc *parent; // pointer to parent process
    int kstack[SSIZE];   // kmode stack of task. SSIZE = 1024.
} PROC;

// Global variables
PROC proc[NPROC], *running, *freeList, *readyQueue;
int procSize = sizeof(PROC);
int color = 0x0C;
int printf(const char *fmt, ...);

// External functions
extern int tswitch(void);
extern int getc(void);
int printf(const char *fmt, ...);

// Function prototypes
int body();
int initialize();
int scheduler();

PROC *get_proc(PROC **list);
int put_proc(PROC **list, PROC *p);

int enqueue(PROC **queue, PROC *p);
PROC *dequeue(PROC **queue);

PROC *kfork();

void printQueue(PROC *queue);
void help();

// 2. Initialize all PROCs
int initialize()
{
    int i;
    PROC *p;

    printf("Initializing...\n");

    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        p->pid = i; // pid = 0,1,2, NPROC - 1
        p->status = FREE;
        p->priority = 0;
        p->ppid = 0;
        p->parent = 0;
        p->next = &proc[i + 1]; // point to next proc
    }

    // set up the 'root' process
    proc[NPROC - 1].next = NULL;
    running = &proc[0];
    running->status = READY;
    running->parent = &proc[0];
    freeList = &proc[1];
    readyQueue = 0;

    printf("Initialization complete\n");
    return 0;
}

// 3. Create a process dynamically
PROC *kfork()
{
    printf("Forking... ");

    int i;
    PROC *p = get_proc(&freeList);
    if (!p)
    {
        printf("No more PROC's, kfork() failed\n");
        return 0;
    }

    //  initialize the proc status, priority, ppid, parent...
    p->status = READY;
    p->priority = 1;
    p->ppid = running->pid;

    /* initialize new proc's kstack[ ] */
    for (i = 1; i < 10; i++)
        p->kstack[SSIZE - i] = 0;

    // resume point = address of body(void)
    // (the function that runs for this process)
    p->kstack[SSIZE - 1] = (int)body;

    p->ksp = &p->kstack[SSIZE - 9];
    enqueue(&readyQueue, p);

    printf("Fork Complete!\n");
    return p;
}

// 4. Get a FREE PROC from a list
PROC *get_proc(PROC **list)
{
    PROC *p;
    if (*list == NULL)
        return 0;

    p = *list;
    *list = (*list)->next;
    p->next = NULL;
    p->status = FREE;

    return p;
}

// Return a PROC to a list (e.g. freeList)
int put_proc(PROC **list, PROC *p)
{
    p->status = FREE;
    p->next = *list;
    *list = p;
    return 0;
}

// 5. Insert a PROC into a priority queue
int enqueue(PROC **queue, PROC *p)
{
    PROC *q = *queue;

    // Case 1: empty queue
    if (!q)
    {
        *queue = p;
        (*queue)->next = NULL;
    }
    // Case 2: process in queue is higher
    else if (p->priority <= q->priority) //
    {
        while (q->next && q->next->priority >= p->priority)
            q = q->next;
        // stops with q being the immediate predecessor for p

        p->next = q->next;
        q->next = p;
    }
    // Case 3: process p has the highest priority
    else
    {
        p->next = (*queue);
        (*queue) = p;
    }

    return 0;
}

// Remove and return first PROC in queue
PROC *dequeue(PROC **queue)
{
    PROC *p = *queue;
    if (*queue != NULL)
        *queue = (*queue)->next;
    return p;
}

// 6. Print the queue in "[pid, priority]->" format
void printQueue(PROC *queue)
{
    printf("\nQueue: ");
    if (!queue)
    {
        printf("There are no processes in this queue\n");
        return;
    }

    while (queue)
    {
        printf("[%d, %d] -> ", queue->pid, queue->priority);
        queue = queue->next;
    }
    printf("NULL\n");
}

// 7. The process scheduler
int scheduler()
{
    printf("Switching...\n");
    if (running->status == READY)
    {
        enqueue(&readyQueue, running);
    }
    running = dequeue(&readyQueue);
    printf("Scheduler finished!\n");

    return 0;
}

// 8. Print available commands
void help()
{
    printf("\nAvailable Commands: \n");
    printf(" - s: Switch to the next ready process.\n");
    printf(" - f: Fork a new process.\n");
    printf(" - ?: This help message.\n");
}

// 10. Run the OS
int main()
{
    printf("\nWelcome to the CS460 Multitasking System!\n");
    help();

    initialize();
    kfork();
    tswitch();

    printf("\nGoodbye User!\n");
}

// Process body code — runs when process is tswitched in
int body()
{
    char c;
    while (1)
    {
        // change the text color based on the process id
        color = 0x01 + (running->pid % NPROC);

        printf("\n******************************\n");
        printf("Currently Running Process #%d", running->pid);
        printQueue(readyQueue);

        c = getc();
        printf("\n");

        switch (c)
        {
        case 's':
            tswitch();
            break;
        case '?':
            help();
            break;
        case 'f':
            kfork();
            break;
        }
    }
}
