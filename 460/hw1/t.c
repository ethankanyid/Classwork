/************ t.c file **********************************/
#define NPROC     9
#define SSIZE  1024                /* kstack int size */

/* proc statii     */
#define FREE      0
#define READY     1
#define SLEEP     2
#define BLOCK     3
#define ZOMBIE    4

// define null, cause it ain't defined otherwise!
#define NULL  0
#define null  0

// 1. Define the structure PROC
typedef struct proc{
struct proc *next;
int *ksp; /* saved sp when PROC is not running*/
int status; /* FREE|READY|SLEEP|BLOCK|ZOMBIE */
int priority; // the priority!
int pid; // the process pid
int ppid; // the parent pid
struct proc *parent; // pointer to parent proc
int kstack[SSIZE]; // kmode stack of task. SSIZE = 1024.
}PROC;


/**** USE YOUR OWN io.c with YOUR printf() here *****/
PROC proc[NPROC], *running; //*freeList, *readyQueue;
int  procSize = sizeof(PROC);
int  color = 0x0C;
// define the functions so things don't break! cause c!
int body();
int initialize();
int scheduler();


//2. Initialize the proc's
int initialize()
{
    running = &proc[0];
    printf("Initialization complete\n");
}

// 7. Scheduler
/****************************************************************
Use the MODIFIED scheduler() function propose in class
*****************************************************************/
// schedule ALL the processes!
int scheduler()
{
    running = &proc[0];
    printf("Scheduler finished\n");
    //Use the MODIFIED scheduler() function propose in class
}



// 10. Run the os!
main()
{
    printf("\nWelcome to the CS460 Multitasking System New User!\n");

    printf("initializing...");
    initialize();

    //printf("forking...");
    //kfork();

    //printf("switching...");
    //tswitch();

    printf("\nGoodbye User!\n");
}

int body()
{
    char c;
    while(1)
    {
        // change the text color based on the process id!
        color = 0x01 + (running->pid % NPROC);
        printf("\n******************************\n");
        printf("Currently Running Process #%d", running->pid);
    }
}
