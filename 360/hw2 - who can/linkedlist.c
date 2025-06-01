#include "linkedlist.h"

/*  Function to operate on Node creating a new node
    returns pointer to the node created
    initializes next as null*/
Node* createNode(void);

Node* createNode(void)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for a new node
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->next = NULL;
    newNode->name = NULL;

    return newNode;
}

void push_back(Node** head, const char *path)
{
    Node* newNode = createNode();  // Create a new node
    if (newNode == NULL)
    {
        printf("Failed to create Node\n");
        return;
    }

    newNode->name = strdup(path);  // Duplicate the string for the node's name
    if (newNode->name == NULL)
    {
        fprintf(stderr,"Failed to duplicate string\n");
        free(newNode);  // Free the node memory if strdup fails
        return;
    }

    if (*head == NULL)
    {
        *head = newNode;  // If the list is empty, make the new node the head
    }
    else
    {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    return;
}

void freeList(Node* head)
{
    Node* temp = head;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
    head = NULL;
}

void printList(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {
        printf ("%s\n", temp->name);
        temp = temp->next;
    }
}

Node* deleteNode(Node** head, Node* node)
{
    if (*head == node)  // Special case: deleting the head
    {
        *head = node->next;
        free(node->name);
        free(node);
        return *head;
    }

    Node* temp = *head;
    while (temp != NULL && temp->next != node)
    {
        temp = temp->next;
    }

    if (temp != NULL)
    {
        temp->next = node->next;
        free(node->name);
        free(node);
    }
    return temp->next;
}

// Bubble Sort function for singly linked list
void bubbleSort(Node** head)
{
    if (head == NULL)
        return;

    Node* i = NULL;
    int swapped = 0;

    // Outer loop to iterate over the entire list
    do
    {
        swapped = 0;
        i = *head;

        // Inner loop to compare adjacent nodes
        while (i != NULL && i->next != NULL)
        {
            if (strcmp(i->name, i->next->name) > 0)
            {
                char* temp = i->name;
                i->name = i->next->name;
                i->next->name = temp;

                swapped = 1;
            }
            i = i->next;
        }
    } while (swapped); // Continue until no more swaps are needed
}
