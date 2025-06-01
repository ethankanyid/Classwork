#include <stdio.h> // for standard I/O functions
#include <string.h> // for strlen()
#include <ctype.h> // for tolower()
#define MAX_LINE_LENGTH 1024 // assume no lines longer than this int


int isAPalindrome(char line[])
{
    int i=0, j;
    char buf[MAX_LINE_LENGTH];
    strcpy(buf, line);
    j=strlen(buf)-1;
   
    while (i<j)
    {
        if (buf[i] != buf[j])
        {
            tolower(buf[i]);
            tolower(buf[j]);
            if (buf[i] != buf[j])
            {
                return 0;
            }
        }
        else
        {
            i++; j--;
        }
            
    }
    return 1;
}


int main(void)
{
char word[MAX_LINE_LENGTH];

    printf("Enter a word: ");
    fgets(word, MAX_LINE_LENGTH, stdin);
    
    if (word[strlen(word)-1]=='\n')
    {
        word[strlen(word)-1]='\0';
    }
        
        
    if (isAPalindrome(word)==1)
    {
        printf("%s is a palindrome\n",word);
    }
    else
    {
        printf("%s is not a palindrome\n",word);
    }

    
return 0;
}
