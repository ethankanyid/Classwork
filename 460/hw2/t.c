#include "structs.h"

int main()
{
    printf("Initializing MTX pre-lab system...\n");
    initialize();
    kfork();
    body();
    return 0;
}
