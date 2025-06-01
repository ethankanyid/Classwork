#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main ()
{
    srand((unsigned int)time (NULL));
    
    int x, randomnumber;
    double sum=0;
    
    printf("please enter the size array you would like: ");
    scanf("%d",&x);
    
    int array[x];
    
    for (int i=0;i<x;i++)
    {
        array[i]=0;
        //printf("%d %d\n",i,array[i]); //to show each value as zero
    }
    
    for (int i=0;i<x;i++)
    {
        
        array[i]= rand()%1000+1;
        //printf("%d\n",array[i]); // to show the random number
    }
    
    for (int i=0;i<x;i++)
    {
        
        sum = sum + array[i];
        //printf("%lf\n",sum); //to show the continuous sum
        
    }
    printf("The sum is: %.2lf\n",sum);
    
    printf("The average is: %.3lf\n",sum=sum/x);
    
    printf("Please enter a number between 1-1000: ");
    scanf("%d",&randomnumber);
    
    sum = 0;
    for (int i=0; i<x;i++)

    {
        if (array[i]== randomnumber)
            sum= sum +1;
    }
    printf("the number %d occurs %d times.\n",randomnumber,(int)sum);
    

    return 0;
}
