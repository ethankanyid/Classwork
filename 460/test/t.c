#include "structs.h"

// 10. Run the OS
int main()
{
    printf("\nWelcome to the CS460 Multitasking System!\n");
    help();

    initialize();
    kfork();
    tswitch();

    printf("\nGoodbye User!\n");
}
