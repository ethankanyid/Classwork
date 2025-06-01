/* Programmer: Ethan Kanyid
 * Class: CptS 121, Fall 2023
 * Programming Lab: Lab 4
 * Date: 9.15.2023
 * Description: This program generates Pascal's Triangle as a triangle.
 */

#include <stdio.h>

int main(void)
{

    int N;

    printf("Please enter a positive integer greater than 0:");
    scanf("%d",&N);
    printf("\n Pascals Triangle:\n");


    for (int n=0;n<=N;n++){
        
        for(int s=1;s<=N-n;s++){
            printf("  ");
        }
        
        int coef =1;
        
        
        for (int r=1;r<=n;r++){

            printf("%4d",coef);
        
            coef = coef * (n + 1 - r) / r  ;

        }
        printf("%4d\n",coef);
    }

return 0;

}