#include "structs.h"

// 2. Initialize all PROCs
int initialize()
{
    int i;
    PROC *p;

    printf("Initializing... ");

    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        p->event = -1;
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

    printf("Initialization complete!\n");
    return 0;
}

// 8. Print available commands
void help()
{
    printf("\nAvailable Commands: \n");
    printf(" - s: Switch to the next ready process.\n");
    printf(" - f: Fork a new process.\n");
    printf(" - ?: This help message.\n");
    printf("\n");
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
