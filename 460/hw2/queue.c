#include "structs.h"
#include <stdio.h>

PROC *get_proc()
{
    return dequeue(&freeList);
}

void put_proc(PROC *p)
{
    p->status = FREE;
    enqueue(&freeList, p);
}

PROC *dequeue(PROC **queue)
{
    PROC *p = *queue;
    if (!p)
        return NULL;
    *queue = p->next;
    p->next = NULL;
    return p;
}

// Priority-based enqueue
void enqueue(PROC **queue, PROC *p)
{
    PROC *q, *prev = 0;

    if (*queue == 0)
    {
        *queue = p;
        p->next = 0;
        return;
    }

    q = *queue;

    if (p->priority > q->priority)
    {
        p->next = q;
        *queue = p;
        return;
    }

    while (q && p->priority <= q->priority)
    {
        prev = q;
        q = q->next;
    }

    prev->next = p;
    p->next = q;
}

void printQueue(PROC *queue)
{
    PROC *p = queue;
    printf("[");
    while (p)
    {
        printf("%d%s", p->pid, p->next ? " -> " : "");
        p = p->next;
    }
    printf("]\n");
}

int scheduler()
{
    if (running->status == READY)
        enqueue(&readyQueue, running);
    running = dequeue(&readyQueue);
    return 0;
}
