#include <stdio.h>

void printStatus(int player, int heapCount1, int heapCount2, int heapCount3); //prints out the player (number) whose turn it is and the current contents of all heaps.
int *setHeapCountPointer(int heap, int *heapCount1_p, int *heapCount2_p, int *heapCount3_p); //returns a pointer to the appropriate heap count, given the heap number.
int getHeap(int heap); //prompts the user for a (legal) heap number.
int getTake(int heap, int heapCount); //prompts the user for a (legal) number of stones to take from a given heap.
int playNim(void); // executes the game


int main(void)
{
       int winner;
       winner = playNim();
    
       printf("player %d wins\n", winner);
    
       return 0;

}

void printStatus(int player, int heapCount1, int heapCount2, int heapCount3)
{
    printf("player %d's turn\n", player);

    printf("(1) ");for (int i=0;i<heapCount1;i++){ printf("O ");}
    printf(" \n");
    printf("(2) ");for (int i=0;i<heapCount2;i++){ printf("O ");}
    printf(" \n");
    printf("(3) ");for (int i=0;i<heapCount3;i++){ printf("O ");}
    printf(" \n");
}

int *setHeapCountPointer(int heap, int *heapCount1_p, int *heapCount2_p, int *heapCount3_p)
{
    int *heapCount_p=0;
    switch (heap)
    {
        case 1:
            heapCount_p = heapCount1_p;
            break;
        case 2:
            heapCount_p = heapCount2_p;
            break;
        case 3:
            heapCount_p = heapCount3_p;
            break;
    }
    return heapCount_p;
}

int getHeap(int heap)
{
    for (;;)
    {
        printf("heap to take stones from (1 - 3): ");
        scanf("%d", &heap);
        if (1 <= heap && heap <= 3)
        {
            break;
        }
        printf("no such heap -- try again\n");
    }
    
    return heap;
}

int getTake(int heap, int heapCount)
{
    int take;
    for (;;)
    {
        printf("count of stones to take from heap %d (1 - %d): ",
               heap, (heapCount));
        scanf("%d", &take);
        
        if (1 <= take && take <= (heapCount))
        {
            break;
        }
        printf("illegal stone count -- try again\n");
    }
    return take;
}

int playNim(void)
{
       int heapCount1, heapCount2, heapCount3;
       int heap=0, player=2, take=0;
       int *heapCount_p;

       heapCount1 = 3;
       heapCount2 = 4;
       heapCount3 = 5;

       while (heapCount1 + heapCount2 + heapCount3 > 0)
       {
           player = 3 - player;
           printStatus(player, heapCount1, heapCount2, heapCount3);
           
           for (;;)
           {
               heap = getHeap(heap);
               heapCount_p = setHeapCountPointer(heap, &heapCount1, &heapCount2, &heapCount3);
               
               if ((*heapCount_p) > 0)
               {
                   break;
               }
               printf("heap %d contains no stones -- try again\n", heap);
           }
           
           take = getTake(heap, *heapCount_p);
           
           (*heapCount_p) -= take;
           printf("\n");
       }
    
       return player;
}
