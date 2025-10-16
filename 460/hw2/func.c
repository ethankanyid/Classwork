#include "structs.h"

PROC proc[NPROC], *running, *freeList, *readyQueue;
int procSize = sizeof(PROC);
int color = 0x0C;

int initialize()
{
    int i;
    PROC *p;
    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        p->pid = i;
        p->status = FREE;
        p->priority = 0;
        p->ppid = 0;
        p->parent = 0;
        p->next = (i < NPROC - 1) ? &proc[i + 1] : 0;
    }
    freeList = &proc[0];
    readyQueue = 0;

    p = get_proc();
    p->status = READY;
    p->priority = 1;
    running = p;
    return 0;
}

void help()
{
    printf("\nAvailable Commands:\n");
    printf(" s - Switch to next ready process\n");
    printf(" f - Fork a child process\n");
    // add more commands
    printf(" ? - Show this help menu\n");
}

// Process body code — runs when process is tswitched in
int body()
{
    char c;

    while (1)
    {
        color = 0x01 + (running->pid % NPROC);

        printf("\n==============================\n");
        printf("Running process: P%d\n", running->pid);
        printf("ReadyQueue: ");
        printQueue(readyQueue);
        printf("Command [s | f | ? | q]: ");

        c = getc();
        printf("\n");

        switch (c)
        {
        case 's':
            scheduler();
            break;
        case 'f':
            kfork();
            break;
        case '?':
            help();
            break;
            // add more commands
        case 'q':
            return 0;
        default:
            printf("Invalid command.\n");
            break;
        }
    }
}
