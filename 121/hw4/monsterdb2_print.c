#include <stdio.h>
#include <stdlib.h>

#include "monsterdb2.h"

int main(void)
    {
        if (monsterdb_load("monsters2.csv") <= 0) {
            fprintf(stderr, "unable to load database -- exiting\n");
            exit(1);
        }
        monsterdb_print();
        return 0;
    }
