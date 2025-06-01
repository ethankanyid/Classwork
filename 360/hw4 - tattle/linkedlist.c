#include "linkedlist.h"

/*  helper function for bubble sort */
static void swapNodes(Node** head, Node* a, Node* b);

Node* createNode(void)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for a new node
    if (newNode == NULL)
    {
        perror("Memory allocation failed");
        return NULL;
    }

    newNode->next = NULL;
    newNode->prev = NULL;

    newNode->record.login[0] = '\0';
    newNode->record.tty[0] = '\0';
    newNode->record.from_host[0] = '\0';

    newNode->record.logoutTime = 0;
    newNode->record.loginTime = 0;
    newNode->record.isLoggedOff = 0;

    return newNode;
}

void pushBack(Node** head, Node* newNode)
{
    if (newNode == NULL)
    {
        perror("Invalid Node\n");
        return;
    }

    if (*head != newNode)
    {
        Node* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
        newNode->prev = temp;  // Set the previous pointer of the new node
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
        free(temp);
    }
    head = NULL;
}

void printList(Node* head)
{
    int colonIndent = 20;

    printf("%-*s %-*s %-*s %-*s %-*s\n",
           colonIndent, "login",
           colonIndent, "tty",
           colonIndent, "log on",
           colonIndent, "log off",
           colonIndent, "from host");

    Node* temp = head;
    while (temp != NULL)
    {
        char bufin[80];
        char bufout[80];
        struct tm loginTimeStruct, logoutTimeStruct;
        localtime_r(&temp->record.loginTime, &loginTimeStruct);
        localtime_r(&temp->record.logoutTime, &logoutTimeStruct);
        strftime(bufin, 80, "%m/%d/%y %H:%M", &loginTimeStruct);
        strftime(bufout, 80, "%m/%d/%y %H:%M", &logoutTimeStruct);

        printf("%-*s %-*s %-*s %-*s %-*s\n",
               colonIndent, temp->record.login,
               colonIndent, temp->record.tty,
               colonIndent, bufin,
               colonIndent, ((temp->record.isLoggedOff == 0) ? "(still logged in)" : bufout),
               colonIndent, temp->record.from_host);

        temp = temp->next;
    }
}

Node* deleteNode(Node** head, Node* node)
{
    if (*head == NULL || node == NULL)
    {
        return NULL;  // Return if the list is empty or the node is NULL
    }

    // If the node to be deleted is the head of the list
    if (*head == node)
    {
        *head = (*head)->next;  // Move the head pointer to the next node
        if (*head != NULL)
        {
            (*head)->prev = NULL;  // Update the prev pointer of the new head
        }
        free(node);
        return *head;
    }

    // If the node to be deleted is not the head, update pointers of surrounding nodes
    if (node->prev != NULL)
    {
        node->prev->next = node->next;  // Update the next pointer of the previous node
    }

    if (node->next != NULL)
    {
        node->next->prev = node->prev;  // Update the prev pointer of the next node
    }

    Node* temp = node->next;

    free(node);  // Free the memory of the node
    return temp;
}

static void swapNodes(Node** head, Node* a, Node* b)
{
    if (a == b || a == NULL || b == NULL)
        return;

    // Handle adjacency
    if (a->next == b)
    {
        // Direct neighbors (a before b)
        a->next = b->next;
        b->prev = a->prev;

        if (b->next)
            b->next->prev = a;

        if (a->prev)
            a->prev->next = b;

        b->next = a;
        a->prev = b;
    }
    else if (b->next == a)
    {
        // Direct neighbors (b before a)
        swapNodes(head, b, a);  // just swap positions
        return;
    }
    else
    {
        // Non-adjacent nodes
        Node* tempPrev = a->prev;
        Node* tempNext = a->next;

        a->prev = b->prev;
        a->next = b->next;

        b->prev = tempPrev;
        b->next = tempNext;

        if (a->prev) a->prev->next = a;
        if (a->next) a->next->prev = a;
        if (b->prev) b->prev->next = b;
        if (b->next) b->next->prev = b;
    }

    // Update head if necessary
    if (*head == a)
        *head = b;
    else if (*head == b)
        *head = a;
}

void bubbleSort(Node** head)
{
    if (head == NULL || *head == NULL)
        return;

    int swapped;
    Node* ptr;
    Node* lastSorted = NULL;

    do
    {
        swapped = 0;
        ptr = *head;

        while (ptr->next != lastSorted)
        {
            if (ptr->record.loginTime > ptr->next->record.loginTime)
            {
                swapNodes(head, ptr, ptr->next);
                swapped = 1;

                // After swapping, ptr moved one step forward
                if (ptr->prev)
                    ptr = ptr->prev;
            }
            ptr = ptr->next;
        }
        lastSorted = ptr;
    } while (swapped);
}

void randomizeList(Node** head)
{
    if (head == NULL || *head == NULL)
        return;

    // Step 1: Count nodes
    int count = 0;
    Node* temp = *head;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    // Step 2: Store pointers in array
    Node** nodeArray = malloc(count * sizeof(Node*));
    temp = *head;
    for (int i = 0; i < count; ++i)
    {
        nodeArray[i] = temp;
        temp = temp->next;
    }

    // Step 3: Shuffle using Fisher-Yates
    srand(time(NULL));
    for (int i = count - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        Node* tmp = nodeArray[i];
        nodeArray[i] = nodeArray[j];
        nodeArray[j] = tmp;
    }

    // Step 4: Rebuild linked list from shuffled array
    for (int i = 0; i < count; ++i)
    {
        nodeArray[i]->prev = (i > 0) ? nodeArray[i - 1] : NULL;
        nodeArray[i]->next = (i < count - 1) ? nodeArray[i + 1] : NULL;
    }

    *head = nodeArray[0];

    free(nodeArray);
}
