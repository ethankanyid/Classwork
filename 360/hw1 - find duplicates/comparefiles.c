#include <stdio.h> // for FILE, NULL, fopen(), and getc()
#include "comparefiles.h"

/*  returns 0 if false 1 if true */
int compareFiles(char *fname0, char *fname1)
{
    FILE *one = fopen(fname0, "r");
    if (one == NULL)
    {
        printf("Could not open %s in compare files\n", fname0);
        return 0;
    }

    FILE *two = fopen(fname1, "r");
    if (two == NULL)
    {
        printf("Could not open %s in compare files\n", fname1);
        return 0;
    }

    char ch1 = 0;
    char ch2 = 0;


    while ((ch1 = fgetc(one)) && (ch2 = fgetc(two)))
    {
        if(ch1 != ch2)
        {
            return 0;
        }
        else if (ch1 == EOF && ch2 == EOF)
        {
            break;
        }
    }

    fclose(one);
    fclose(two);



    return 1;
}
