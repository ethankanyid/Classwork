#include "structs.h"
#include <stdio.h>

PROC *kfork()
{
    PROC *p = get_proc();
    if (!p)
    {
        printf("kfork failed: no free PROC\n");
        return NULL;
    }

    p->status = READY;
    p->priority = 1;
    p->ppid = running->pid;
    p->parent = running;

    for (int i = 1; i < 10; i++)
        p->kstack[SSIZE - i] = 0;
    p->kstack[SSIZE - 1] = (int)body;
    p->ksp = &(p->kstack[SSIZE - 9]);

    enqueue(&readyQueue, p);
    printf("Process %d forked child %d\n", running->pid, p->pid);
    return p;
}

void ksleep(int event)
{ /* TODO: implement sleep */
}

void kwakeup(int event)
{ /* TODO: implement wakeup */
}

void kexit()
{ /* TODO: implement exit */
}

void kwait()
{
    printf("kwait not implemented yet\n");
}

void kstop()
{ /* TODO: implement stop */
}

void kcontinue()
{
    printf("Continuing stopped processes (not implemented)\n");
}
