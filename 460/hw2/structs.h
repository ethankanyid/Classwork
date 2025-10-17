#ifndef STRUCTS_H
#define STRUCTS_H

#define NPROC 9
#define SSIZE 1024 /* kstack int size */

// Define null since it doesn't exist
#define NULL 0

// Process status codes
#define FREE 0
#define READY 1
#define SLEEP 2
#define BLOCK 3
#define ZOMBIE 4
#define STOP 5
#define DEAD 6

// PROC structure definition
typedef struct proc
{
    struct proc *next;
    int event;
    int *ksp;            // saved sp when PROC is not running
    int status;          // FREE|READY|SLEEP|BLOCK|ZOMBIE
    int priority;        // scheduling priority
    int pid;             // process ID
    int ppid;            // parent process ID
    struct proc *parent; // pointer to parent process
    int kstack[SSIZE];   // kmode stack of task. SSIZE = 1024.
} PROC;

/* Global variables */
PROC proc[NPROC], *running, *freeList, *readyQueue;
int procSize = sizeof(PROC);
int color = 0x0C;

/* external functions */
extern int tswitch(void);
extern int getc(void);
int printf(const char *fmt, ...);

/* Function prototypes */
int body();
int initialize();
int scheduler();

PROC *get_proc();
void put_proc(PROC *p);
void enqueue(PROC **queue, PROC *p);
PROC *dequeue(PROC **queue);
void printQueue(PROC *queue);

void help();

PROC *kfork();

/* Kernel functions */
void ksleep();
void kwakeup();
void kexit();
// void kwait();
void kstop();
void kcontinue();

#endif
