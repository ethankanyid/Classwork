#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 50


void string_reverse(char string[MAX_STRING_LENGTH]);

int main() {
    
    char string[MAX_STRING_LENGTH];
    
    printf("Please enter string to be reversed: ");
    scanf("%s",string);
    
    string_reverse(string);
    
    printf("This is the string reversed: %s\n",string);
    

    return 0;
}


void string_reverse(char string[MAX_STRING_LENGTH])
{

    char temp;
    int i=0;
    
    while (string[i]!='\0')
    {
        i++;
    }
    
    for (int x=0;x<i/2;x++)
    {
        temp=string[x];
        string[x]=string[i-x-1];
        string[i-x-1]=temp;
    }
}
