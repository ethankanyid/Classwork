#include <stdio.h>
#include <stdlib.h>

#include "monsterdb2.h"

int compareMonstersByYear(const void *monster0_vp, const void *monster1_vp)
    {
        const struct Monster *monster0_p = monster0_vp;
        const struct Monster *monster1_p = monster1_vp;

        return monster0_p->year - monster1_p->year;
    }

int main(void)
    {
        if (monsterdb_load("monsters2.csv") <= 0) {
            fprintf(stderr, "unable to load database -- exiting\n");
            exit(1);
        }
        monsterdb_sortUsing(compareMonstersByYear);
        monsterdb_printCsv();
        
        return 0;
    }
