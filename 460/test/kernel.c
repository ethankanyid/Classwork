#include "structs.h"

PROC proc[NPROC], *running, *freeList, *readyQueue;
int procSize = sizeof(PROC);
int color = 0x0C;

// 3. Create a process dynamically
PROC *kfork()
{
    int i;
    PROC *p;

    printf("Forking... ");

    p = get_proc(&freeList);
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
