#include "structs.h"

int main()
{
    printf("Initializing MTX pre-lab system...\n");
    help();

    initialize();
    kfork();
    tswitch();

    return 0;
}
