/* Programmer: Ethan Kanyid
 * Class: CptS 121, Spring 2023
 * Programming lab: Lab05
 * Date: 9-22-2023
 * Description: Pascal Triangle with Arrays
 */


#include <stdio.h>
#define MAX_ROWS 16
int main(void)
{

    int oldRow[MAX_ROWS+1];
    int newRow[MAX_ROWS+1];
    
    for (int n=0;n<=MAX_ROWS;n++)
    {
        for(int m=0;m<=n;m++)
        {
            
            if (m==0)
            {
                newRow[m]=1;
            }
            else if (m==n)
            {
                newRow[m]=1;
            }
            else
            {
                newRow[m]= oldRow[m]+oldRow[m-1];
            }
        }
            for (int m=0;m<=n;m++)
            {
                printf("%d ",newRow[m]);
                oldRow[m]=newRow[m];
            }
            
            printf("\n");
    }
    return 0;
}
