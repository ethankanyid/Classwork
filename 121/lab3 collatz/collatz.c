/** Programmer: Ethan Kanyid
* Class: CptS 121, Spring 2011 
* Programming lab: Lab_03
* Date: 9-8-2023
* Description: collatz problem
*/

#include <stdio.h>


int main(void)
{
    int n;

    printf("Please enter an Integer:");
    scanf("%d",&n);

    if (n<=0)
    {
        printf("error\n");
    }
    
    else
    {
    while (n != 1)
    {
        if (n%2==0)
        {
            n=n/2;
        }
        else 
        {
            n=(n*3)+1;
        }
    }
    printf("%d\n",n);
    }
return 0;
}