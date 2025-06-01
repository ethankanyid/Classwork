#ifndef LINKED_LIST_H   // Include guard
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <time.h>
#include <string.h>

#define MAX_URL 2048

typedef struct url
{
    char url[MAX_URL];
    int status;
} url;

/*  Define the structure for a node in the linked list*/
typedef struct Node
{
    url data;
    struct Node* next;
    struct Node* prev;

} Node;

/*  Function to operate on Node creating a new node
    returns pointer to the node created
    initializes next as null*/
Node* createNode(void);

/*  pushes a new node at the end of the list*/
void pushBack(Node** head, Node* newNode);

/*  Function to operate by deallocating list memory*/
void freeList(Node* head);

/*  prints a list to standard out */
void printList(Node* head);

/*  finds the last of a TTY in the list, returns node */
Node* findLastOf(Node* head, const char* logOffTTY);

/*  returns the new node where node was.
    check if null*/
Node* deleteNode(Node** head, Node* node);

/*  sorts the list by comparing strings.
    sorts alphabetically using strcmp.
    changes order by value, not pointer, since head cannot change*/
void bubbleSort(Node** head);

/*  test to make sure sort works */
void randomizeList(Node** head);

/*  removes duplicates from the list */
void checkDups(Node** head);

#endif // LINKED_LIST_H
