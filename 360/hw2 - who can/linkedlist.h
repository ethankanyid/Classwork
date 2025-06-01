#ifndef LINKED_LIST_H   // Include guard
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>

/*  Define the structure for a node in the linked list*/
typedef struct Node
{
    char* name;
    struct Node* next;

} Node;

/*  pushes a new node at the end of the list*/
void push_back(Node** head, const char *path);

/*  Function to operate by deallocating list memory*/
void freeList(Node* head);

/*  prints a list to standard out */
void printList(Node* head);

/*  returns the new node where node was.
    check if null*/
Node* deleteNode(Node** head, Node* node);

/*  sorts the list by comparing strings.
    sorts alphabetically using strcmp.
    changes order by value, not pointer, since head cannot change*/
void bubbleSort(Node** head);

#endif // LINKED_LIST_H
