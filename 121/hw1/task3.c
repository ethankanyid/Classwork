//
//  main.c
//  Task3
//
//  Created by Ethan Kanyid on 9/16/23.
//

#include <stdio.h>
int main()
{
    int i=0,n=0,nextTerm=0;
    
   
    while (nextTerm == 0)
    {
        i = n + nextTerm ;
        n = nextTerm;
        nextTerm = i;
        printf("%d\n",i);
        nextTerm=1;
        
    }
    
    
    for (int x=0;x<10;x++)
    {
        
        i = nextTerm + n;
        n = nextTerm;
        nextTerm = i;
        printf("%d\n",i);
        
    }
    

    
return 0;
}
