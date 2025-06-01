#ifndef LINKED_LIST_H   // Include guard
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_PATH 4096

/*  Define the structure for a node in the linked list*/
typedef struct Node
{
    char* path;
    off_t size;
    struct Node* next;

    int duplicateSet;
    int duplicateCount;

    bool duplicate;

} Node;

/*  pushes a new node at the end of the list*/
void push_back(const char *path, off_t size);

/*  Function to operate by deallocating list memory*/
void freeList(void);

void printList(void);

void findDuplicates(void);

void printDuplicates(void);

#endif // LINKED_LIST_H
