#include "structs.h"

// 4. Get a FREE PROC from a list
PROC *get_proc(PROC **list)
{
    PROC *p;
    if (*list == NULL)
        return 0;

    p = *list;
    *list = (*list)->next;
    p->next = NULL;
    p->status = FREE;

    return p;
}

// Return a PROC to a list (e.g. freeList)
int put_proc(PROC **list, PROC *p)
{
    p->status = FREE;
    p->next = *list;
    *list = p;
    return 0;
}

// 5. Insert a PROC into a priority queue
int enqueue(PROC **queue, PROC *p)
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

    return 0;
}

// Remove and return first PROC in queue
PROC *dequeue(PROC **queue)
{
    PROC *p = *queue;
    if (*queue != NULL)
        *queue = (*queue)->next;
    return p;
}

// 6. Print the queue in "[pid, priority]->" format
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

// 7. The process scheduler
int scheduler()
{
    printf("Switching... ");
    if (running->status == READY)
    {
        enqueue(&readyQueue, running);
    }
    running = dequeue(&readyQueue);
    printf("Scheduler finished!\n");

    return 0;
}
