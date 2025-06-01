#include "linkedlist.h"
#include "comparefiles.h"

/*  Function to operate on Node creating a new node
    returns pointer to the node created
    initializes next and prev as null*/
static Node* createNode(const char *path, off_t size);

static Node* head = NULL;
static Node* tail = NULL;

static Node* createNode(const char *path, off_t size)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for a new node
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->next = NULL;
    newNode->path = strdup(path);
    newNode->size = size;
    newNode->duplicate = false;
    newNode->duplicateSet = 0;
    newNode->duplicateCount = 0;

    return newNode;
}

void push_back(const char *path, off_t size)
{
    Node* newNode = createNode(path, size);  // Create a new node
    if (newNode == NULL)
    {
        printf("Failed to create Node\n");
        return;
    }
    if (head == NULL)
    {
        head = tail = newNode;  // If the list is empty, make the new node the head
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }

    return;
}

void freeList(void)
{
    Node* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->path);
        free(temp);
    }
    head = tail = NULL;
}

void printList(void)
{
    Node* temp = head;
    for (int i = 0; temp != NULL; i++)
    {
        printf ("%d %s\n", i, temp->path);
        temp = temp->next;
    }
}

void printDuplicates(void)
{
    Node* temp = head;
    int max = 2;
    int i = 1;

    //i think its a dumb requirement that the first number printed is the count of items in the set
    //it should a number indicating which set it belongs to relatively.
    // a whole nother loop for nothing.
    // could be short circuited when sizes do not match because list is sorted.
    // alternatively couldve just used separate list...
    while(temp != NULL)
    {
        i = 1;
        max = 2;
        if (temp->duplicate)
        {
            Node* tempInner = temp->next;
            while (tempInner != NULL)
            {
                if (temp->duplicateSet == tempInner->duplicateSet)
                {
                    max = (max < tempInner->duplicateCount) ? tempInner->duplicateCount : max;
                }
                tempInner = tempInner->next;
            }
            printf ("%d %d %s\n", max, i, temp->path);

            tempInner = temp->next;
            while (tempInner != NULL)
            {
                if (temp->duplicateSet == tempInner->duplicateSet)
                {
                    printf ("%d %d %s\n", max, ++i, tempInner->path);
                    tempInner->duplicate = false; //as to not print twice
                }
                tempInner = tempInner->next;
            }
        }
        temp = temp->next;
    }
}

void findDuplicates(void)
{

    int duplicateSet = 0;
    int duplicatesInSet = 0;
    bool foundDuplicate = false;

    Node* temp = head;

    while (temp != NULL)
    {
        if (temp->duplicate)
        {
            temp = temp->next;
            continue;
        }

        if (foundDuplicate)
            duplicateSet++;
        foundDuplicate = false;
        duplicatesInSet = 1;

        Node* tempInner = temp->next;

        while (tempInner != NULL)
        {
            if((temp->size == tempInner->size) && (compareFiles(temp->path, tempInner->path)))
            {
                foundDuplicate = true;
                temp->duplicate = true;
                tempInner->duplicate = true;
                temp->duplicateSet = duplicateSet + 1;
                tempInner->duplicateSet = duplicateSet + 1;
                temp->duplicateCount = 1;
                tempInner->duplicateCount = ++duplicatesInSet;
            }
            tempInner = tempInner->next;
        }
        temp = temp->next;
    }

    if (duplicateSet == 0)
    {
        printf("No Duplicates\n");
    }
}
