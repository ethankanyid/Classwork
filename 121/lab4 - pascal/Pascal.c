/* Programmer: Ethan Kanyid
 * Class: CptS 121, Fall 2023
 * Programming Lab: Lab 4
 * Date: 9.15.2023
 * Description: This program generates Pascal's Triangle for any positive value of N.
 */

#include <stdio.h>

int main(void)
{

    int N;

    printf("Please enter a positive integer greater than 0:");
    scanf("%d",&N);

    for (int n=0;n<=N;n++){
    
        int coef =1;
    
        for (int r=1;r<=n;r++){

            printf("%d ",coef);
        
            coef = coef * (n + 1 - r) / r  ;

        }
        printf("%d\n",coef);
    }



return 0;
}