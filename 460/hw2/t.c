#include "structs.h"

int main()
{
    printf("Initializing MTX pre-lab system...\n");
    help();

    initialize();
    kfork();
    // body();
    tswitch();

    return 0;
}
