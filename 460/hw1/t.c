/************ t.c file **********************************/
#define NPROC 9
#define SSIZE 1024 /* kstack int size */

/* proc statii     */
#define FREE 0
#define READY 1
#define SLEEP 2
#define BLOCK 3
#define ZOMBIE 4

// define null, cause it ain't defined otherwise!
#define NULL 0
#define null 0

// 1. Define the structure PROC
typedef struct proc
{
    struct proc *next;
    int *ksp;            /* saved sp when PROC is not running*/
    int status;          /* FREE|READY|SLEEP|BLOCK|ZOMBIE */
    int priority;        // the priority!
    int pid;             // the process pid
    int ppid;            // the parent pid
    struct proc *parent; // pointer to parent proc
    int kstack[SSIZE];   // kmode stack of task. SSIZE = 1024.
} PROC;

/**** USE YOUR OWN io.c with YOUR printf() here *****/
PROC proc[NPROC], *running; //*freeList, *readyQueue;
int procSize = sizeof(PROC);
int color = 0x0C;
// define the functions so things don't break! cause c!
int body();
int initialize();
int scheduler();

// PROC *get_proc();
// put_proc(PROC *p);
void enqueue(PROC **queue, PROC *p);
PROC *dequeue(PROC **queue);

void printQueue(PROC *queue);
PROC *kfork();
void help();

// 2. Initialize the proc's
int initialize()
{
    PROC *p;
    int i, j;
    for (int i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        p->pid = i; // pid = 0,1,2, NPROC - 1
        p->status = FREE;
        p->priority = 0;
        p->ppid = 0;
        p->parent = 0;
        p->next = &proc[i + 1]; // point to next proc
    }
    proc[NPROC - 1].next = NULL;
    running = &proc[0];
    running->status = READY;
    running->parent = &proc[0];
    freelist = &proc[1];
    readyQueue = 0;
    running = &proc[0];
    printf("Initialization complete\n");
}

// 5.Enter p into queue (by priority in the next homework)
// create an enqueue method, use three cases:
// Case 1: empty queue. make the passed process a new queue!
// Case 2: non - empty queue, new process has greatest priority. Insert new
// process onto head of the queue. Case 3: non-empty queue, new process needs to
// be inserted somewhere in it. look through the processes in the queue until we
// find a spot where the process' priority will be properly respected.

void enqueue(PROC **queue, PROC *p)
{
    PROC *tmp;
    PROC *prev;

    // Case 1: empty queue. make the passed process a new queue!
    if ((*queue) == NULL)
    {
        *(queue) = p;
        *(queue)->next = NULL;
    }
    // // Case 2: non-empty queue, new process has greatest priority. insert new
    // // process onto head of the queue. else if (p->priority >
    // (*queue)->priority)
    // {
    // }
    // Case 3: non-empty queue, new process needs to be inserted somewhere in
    // it. look through the processes in the queue until we find a spot where
    // the process' priority will be properly respected.
    else
    {
        p->next = *(queue);
        *(queue) = p;
    }
}

// Remove a PROC (highest priority in the next homework)
// order by priority the first one in queue
//  return its pointer;
PROC *dequeue(PROC **queue)
{
    // get the proc we need...
    // and then modify the queue to remove the proc we need...
    // return the proc we deserve!
    PROC *p = *queue;
    if (*queue != NULL)
    {
        *(queue) = *(queue)->next;
    }

    return p;
}

// 7. Scheduler
/****************************************************************
Use the MODIFIED scheduler() function propose in class
*****************************************************************/
// schedule ALL the processes!
int scheduler()
{
    if (running->status == READY)
    {
        enqueue(&readyQueue, running);
    }
    running = dequeue(&readyQueue);
    printf("Scheduler finished\n");
    // Use the MODIFIED scheduler() function propose in class
}

// 8. print info on available commands.
void help()
{
    printf("\nAvailable Commands: \n");
    printf(" - s: Switch to the next ready process.\n");
    printf(" - f: Fork a new process.\n");
    printf(" - ?: This help message.\n");
}

// 10. Run the os!
int main()
{
    printf("\nWelcome to the CS460 Multitasking System New User!\n");

    printf("initializing...");
    initialize();

    // printf("forking...");
    // kfork();

    // printf("switching...");
    // tswitch();

    printf("\nGoodbye User!\n");
}

int body()
{
    char c;
    while (1)
    {
        // change the text color based on the process id!
        color = 0x01 + (running->pid % NPROC);
        printf("\n******************************\n");
        printf("Currently Running Process #%d", running->pid);
        printQueue(readyQueue);
        c = getc();
        printf("\n");
        switch (c)
        {
        case 's':
            do_tswitch();
            break;
        case '?':
            help();
            break;
        case 'f':
            kfork();
            break;
        }
    }
