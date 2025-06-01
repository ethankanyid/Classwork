#ifndef _INCLUDED_MONSTERDB_H /* effectively prevents multiple #includes */

struct Monster {
    char *name;
    char *film;
    int year;
    char *weakness;
    char *defeatedBy;
    double rating;
};

extern struct Monster *monsters_p;

extern int  monsterdb_getCount(void);
extern int  monsterdb_load(char *fileName);
extern void monsterdb_print(void);
extern void monsterdb_printCsv(void);
extern void monsterdb_printHtml(void);
extern void monsterdb_sortUsing(int (*compare_p)(const void *monster0_vp,const void *monster1_vp));

#define _INCLUDED_MONSTERDB_H
#endif
