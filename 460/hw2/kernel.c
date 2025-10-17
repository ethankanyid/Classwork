#include "structs.h"

PROC *kfork()
{
    int i;
    PROC *p;

    p = get_proc(&freeList);
    if (!p)
    {
        printf("kfork failed: no free PROC\n");
        return NULL;
    }

    p->status = READY;
    p->priority = 1;
    p->ppid = running->pid;
    p->parent = running;

    for (i = 1; i < 10; i++)
        p->kstack[SSIZE - i] = 0;
    p->kstack[SSIZE - 1] = (int)body;
    p->ksp = &(p->kstack[SSIZE - 9]);

    enqueue(&readyQueue, p);
    printf("Process %d forked child %d\n", running->pid, p->pid);
    return p;
}

void ksleep(int event)
{
    running->event = event;
    running->status = SLEEP;
    tswitch();
}

void kwakeup(int event)
{
    int i;
    PROC *p;
    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        if (p->status == SLEEP && p->event == event)
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
    char c;

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
void kwait()
{
    printf("kwait not implemented yet\n");
}
