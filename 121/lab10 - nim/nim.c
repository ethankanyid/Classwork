#include <stdio.h>

int main(void)

{

    int heapCount1, heapCount2, heapCount3;
    int heap, player, take,i;
    int *heapCount_p;

    heapCount1 = 3;
    heapCount2 = 4;
    heapCount3 = 5;

    player = 2;
    while (heapCount1 + heapCount2 + heapCount3 > 0)
    {
        player = 3 - player;

        printf("player %d's turn\n", player);

        printf("(1) ");for (i=0;i<heapCount1;i++){ printf("O ");}
        printf(" \n");
        printf("(2) ");for (i=0;i<heapCount2;i++){ printf("O ");}
        printf(" \n");
        printf("(3) ");for (i=0;i<heapCount3;i++){ printf("O ");}
        printf(" \n");

        for (;;)

        {

            for (;;)

            {
                printf("heap to take stones from (1 - 3): ");
                scanf("%d", &heap);

                if (1 <= heap && heap <= 3)
                {
                    break;
                }
                printf("illegal heap value -- try again\n");
            }
            
            switch (heap)
            {
            case 1:
                heapCount_p = &heapCount1;
                break;
            case 2:
                heapCount_p = &heapCount2;
                break;
            case 3:
                heapCount_p = &heapCount3;
                break;
            }
   
            if ((*heapCount_p) > 0)
            {
                break;
            }
            printf("heap %d contains no stones -- try again\n", heap);
        }

        for (;;)
        {
            printf("count of stones to take from heap %d (1 - %d): ",
                   heap, (*heapCount_p));
            scanf("%d", &take);

            if (1 <= take && take <= (*heapCount_p))
            {
                break;
            }
            printf("illegal heap count -- try again\n");
        }

        (*heapCount_p) -= take;
        printf("\n"); // blank line for cosmetic purposes
    }
    
    printf("player %d wins\n", player);

    return 0;
}
