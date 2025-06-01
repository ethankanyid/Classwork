#include <stdio.h> // for standard I/O functions
#include <string.h> // forstrlen()
#include <ctype.h> // for tolower()
#define MAX_LINE_LENGTH 1024 // assume no lines longer than this


void removeNonLetters(char buf[])
{
    int i=0,j=0;
    
    while (buf[j] != '\0')
    {
        if (isalpha(buf[j]))
        {
            buf[i]=buf[j];
            i++;
        }
        j++;
    }
    buf[i]='\0';
}


int isAPalindrome(char line[])
{
    int i=0, j;
    char buf[MAX_LINE_LENGTH];
    strcpy(buf, line);
    removeNonLetters(buf);
    j=strlen(buf)-1;
   
    while (i<j)
    {
        if (tolower(buf[i++]) != tolower(buf[j--]))
        {
            return 0;
        }
    }
    return 1;
}


int main(void){
char line[MAX_LINE_LENGTH];
    
while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL)
{
    if (strlen(line)>=4 && isAPalindrome(line))
    {printf("%s",line);}

}
    
return 0;
}
