// It's not a bad practice to list *why* you include particular
// headers.
#include <stdio.h> // for FILE, NULL, fopen(), and getc()

#include "eprintf.h" // for eprintf_fail()

// Although not strictly required, its a good practice to include the
// header file that corresponds to this source file to detect any
// discrepancies between the function's declaration and its
// definition.
#include "compare_files.h"


int compareFiles(char *fname0, char *fname1)
{
    //
    // ASSIGNMENT
    //
    // This function compares two files named `fname0` and `fname1`
    // and returns true (1) if they are identical or false (0) if they
    // are not. Here's how it would be described in pseudocode (note
    // the indented block structure):
    //
    //   open file 0 for reading (hint: fopen(3))
    //   if the open fails,
    //       exit with an error message
    //   open file 1 for reading (hint: fopen(3))
    //   if the open fails,
    //       exit with an error message
    //   repeat until this function returns:
    //       read a character `ch0` from file 0 (hint: getc(3))
    //       read a character `ch1` from file 1 (hint: getc(3))
    //       compare both characters to each other and to `EOF`,
    //        (possibly) returning 0 or 1
    //
    // The last statement is intentionally vague. The logic here is
    // important. No extra points challenge: It can be done in a
    // single `if`-block.
    //

    FILE *one = fopen(fname0, "r");
    if (one == NULL)
    {
        eprintf_fail("Invalid File\n");
    }

    FILE *two = fopen(fname1, "r");
    if (two == NULL)
    {
        eprintf_fail("Invalid File\n");
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


    return 1;

}
