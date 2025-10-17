#include "structs.h"

int main()
{
    printf("\nWelcome to the CS460 Multitasking System!\n");
    help();

    initialize();
    kfork();
    tswitch();

    printf("\nGoodbye User!\n");
}
