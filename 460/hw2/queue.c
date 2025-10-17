#include "structs.h"

PROC *get_proc()
{
    return dequeue(&freeList);
}

void put_proc(PROC *p)
{
    p->status = FREE;
    p->next = freeList;
    freeList = p;
    // enqueue(&freeList, p);
    return;
}

PROC *dequeue(PROC **queue)
{
    PROC *p = *queue;
    if (*queue != NULL)
        *queue = (*queue)->next;
    return p;
}

// Priority-based enqueue
void enqueue(PROC **queue, PROC *p)
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
}

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

int scheduler()
{
    if (running->status == READY)
        enqueue(&readyQueue, running);
    running = dequeue(&readyQueue);
    return 0;
}
