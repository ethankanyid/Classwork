#include "structs.h"

PROC *kfork()
{
    int i;
    PROC *p;

    p = get_proc(); // FIX?
    if (!p)
    {
        printf("No more PROC's, kfork() failed\n");
        return 0;
    }

    //  initialize the proc status, priority, ppid, parent...
    p->status = READY;
    p->priority = 1;
    p->ppid = running->pid;
    p->parent = running;
    p->event = -1;

    /* initialize new proc's kstack[ ] */
    for (i = 1; i < 10; i++)
        p->kstack[SSIZE - i] = 0;

    // resume point = address of body(void)
    // (the function that runs for this process)
    p->kstack[SSIZE - 1] = (int)body;

    p->ksp = &p->kstack[SSIZE - 9];
    enqueue(&readyQueue, p);

    // printf("Process %d forked child %d\n", running->pid, p->pid);
    return p;
}

void ksleep()
{
    int i;
    int c;

    printf("Select an integer event (0-9): ");

    c = getc() - '0'; // FIX
    printf("\n");

    printf("%d", c);
    if (c < 0 || c > 9)
    {
        printf("Invalid PID.\n");
        return;
    }

    running->event = c;
    running->status = SLEEP;
    tswitch();
}

void kwakeup()
{
    int i;
    PROC *p;
    int c;

    printf("Select an integer event (0-9): ");

    c = getc() - '0'; // FIX
    printf("\n");

    if (c < 0 || c > 9)
    {
        printf("Invalid PID.\n");
        return;
    }

    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        if (p->status == SLEEP && p->event == c)
        {
            p->status = READY;
            enqueue(&readyQueue, p);
        }
    }
}

void kstop()
{
    running->status = STOP;
    tswitch();
}

void kcontinue()
{
    int i;
    PROC *p;
    int c;

    printf("Select a Process to continue(");
    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        if (p->status == STOP)
        {
            printf("%d, ", p->pid);
        }
    }
    printf("): ");
    c = getc() - '0';
    printf("\n");

    p = &proc[c];
    if (p->status == STOP)
    {
        p->status = READY;
        enqueue(&readyQueue, p);
    }
}

void kexit()
{
    running->status = DEAD;
    tswitch();
}

// not implemented
// void kwait()
// {
//     printf("kwait not implemented yet\n");
// }
