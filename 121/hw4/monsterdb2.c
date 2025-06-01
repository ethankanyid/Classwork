#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "monsterdb2.h"

struct Monster *monsters_p;
static int monsterCount=0;


static int foundColumnName(FILE *f_p, char columnName[], char followedBy);

static void printCsvHeader(void);
static void printCsvRow(struct Monster monster);

static void printHtmlTableHeader(void);
static void printHtmlTableRow(struct Monster monster);
static void printMonster(struct Monster monster);

static int scanCsvHeader(FILE *f_p);
static int scanCsvRow(FILE *f_p, struct Monster *monster_p);

static char *fscanToken(FILE *f_p, char delimiter);



static int foundColumnName(FILE *f_p, char columnName[], char followedBy)
    {
        char *token = fscanToken(f_p,followedBy);
            if (token == NULL)
            {
                free(token);
                return 0;
            }
            if(strcmp(token, columnName) != 0)
            {
                free(token);
                return 0;
            }

        free(token);
        return 1;
    }


int monsterdb_getCount(void)
    {
        return monsterCount;
    }


int monsterdb_load(char *fileName)
    {
        FILE *f_p=fopen(fileName,"r");

        struct Monster monster;

        if(f_p ==NULL || scanCsvHeader(f_p)!=1)
        {
            fclose(f_p);
            return 0;
        }

        for (;;)
        {
            if (scanCsvRow(f_p, &monster) != 1)
            {
                break;
            }

            struct Monster *newMonsters_p =(struct Monster*)malloc((monsterCount+1)*sizeof(struct Monster));

            for (int i=0;i<monsterCount;i++)
            {
                newMonsters_p[i] = monsters_p[i];
            }

            newMonsters_p[monsterCount] = monster;
            monsterCount++;
            free(monsters_p);
            monsters_p = newMonsters_p;
        }

        fclose(f_p);

        return monsterCount;
        /*

        * ASSIGNMENT
        *
        * Rewrite the body of this function to implement the following:
        *
        * let `f_p` be the result of fopen()'ing `fileName` for reading
        * if the fopen() fails,
        *     return 0
        * if scanCsvHeader() can't read the header from `f_p`,
        *     close `f_p` with fclose()
        *     return 0
        * loop:
        *     use `scanCsvRow()` to read a row into a Monster struct
        *      `monster`
        *     if it fails,
        *         break out of the loop
        *     call malloc() to allocate a (pointer to a) `newMonsters_p`
        *      array big enough to hold all the old monsters and the new
        *      one (its size will be
        *      `(monsterCount + 1) * sizeof(struct Monster)` bytes)
        *     for each existing monster `i`,
        *         set `newMonsters_p[i]` to `monsters_p[i]`
        *     set `newMonsters_p[monsterCount]` to `monster`
        *     increment `monsterCount`
        *     free the existing `monsters_p` (pointer)
        *     set `monsters_p` to `newMonsters_p`, so that it points to
        *      the (new) block of memory
        * close `f_p` with `fclose()`
        * return `monsterCount`
        */
    }


void monsterdb_print(void)
    {
        int i, count;

        count = monsterdb_getCount();
        for (i = 0; i < count; i++) {
            printMonster(monsters_p[i]);
            putchar('\n');
        }
    }


void monsterdb_printCsv(void)
    {
        int i, count;

        printCsvHeader();
        count = monsterdb_getCount();
        for (i = 0; i < count; i++) {
            printCsvRow(monsters_p[i]);
        }

    }


void monsterdb_printHtml(void)
    {
        int i, count;

        printf("<table>\n");
        printHtmlTableHeader();
        count = monsterdb_getCount();
        for (i = 0; i < count; i++) {
            printHtmlTableRow(monsters_p[i]);
        }
        printf("</table>\n");
    }


void monsterdb_sortUsing(int (*compare_p)(const void *monster0_vp,const void *monster1_vp))
    {
        int monsterCount = monsterdb_getCount();
        qsort(monsters_p, monsterCount, sizeof(struct Monster), compare_p);
    }


static void printCsvHeader(void)
    {
        printf("Name,");
        printf("Film,");
        printf("Year,");
        printf("Weakness,");
        printf("Defeated by,");
        printf("Rating\n");
    }


static void printCsvRow(struct Monster monster)
    {
        printf("%s,",  monster.name);
        printf("%s,",  monster.film);
        printf("%d,",  monster.year);
        printf("%s,",  monster.weakness);
        printf("%s,",  monster.defeatedBy);
        printf("%.1f\n", monster.rating);
    }


static void printHtmlTableHeader(void)
    {
        printf("<tr>\n");
        printf("<th>Name</th>\n");
        printf("<th>Film</th>\n");
        printf("<th>Year</th>\n");
        printf("<th>Weakness</th>\n");
        printf("<th>Defeated by</th>\n");
        printf("<th>Rating</th>\n");
        printf("</tr>\n");
    }


static void printHtmlTableRow(struct Monster monster)
    {
        printf("<tr>\n");
        printf("<td>%s</td>\n",  monster.name);
        printf("<td>%s</td>\n",   monster.film);
        printf("<td>%d</td>\n",   monster.year);
        printf("<td>%s</td>\n",   monster.weakness);
        printf("<td>%s</td>\n",   monster.defeatedBy);
        printf("<td>%.1f</td>\n", monster.rating);
        printf("</tr>\n");
    }


static void printMonster(struct Monster monster)
    {
        int colonIndent = 15;
        
        printf("%*s: %s\n",   colonIndent, "Name",        monster.name);
        printf("%*s: %s\n",   colonIndent, "Film",        monster.film);
        printf("%*s: %d\n",   colonIndent, "Year",        monster.year);
        printf("%*s: %s\n",   colonIndent, "Weakness",    monster.weakness);
        printf("%*s: %s\n",   colonIndent, "Defeated by", monster.defeatedBy);
        printf("%*s: %.1f\n", colonIndent, "Rating",      monster.rating);
    }


static int scanCsvHeader(FILE *f_p)
    {
        if (!foundColumnName(f_p, "Name", ','))
            return 0;
        if (!foundColumnName(f_p, "Film", ','))
            return 0;
        if (!foundColumnName(f_p, "Year", ','))
            return 0;
        if (!foundColumnName(f_p, "Weakness", ','))
            return 0;
        if (!foundColumnName(f_p, "Defeated by", ','))
            return 0;
        if (!foundColumnName(f_p, "Rating", '\n'))
            return 0;
        return 1;
    }


static int scanCsvRow(FILE *f_p, struct Monster *monster_p)
    /* reads a Monster row from a CSV file */
    {
        /*
        * ASSIGNMENT
        *
        * Replace the body of this function to use fscanToken() instead
        * of fscanf() as follows by implementing this pseudocode:
        *
        * let `token` be the result of an fscanToken() call on f_p, expecting
        *  the delimiting character to be `,`
        * if `token` is NULL (there were errors)
        *     return a 0 (i.e. failure) to the caller
        * set `monster_p->name` to `token`
        * 
        * 
        * 
        * do the same for `monster_p->film` as for `monster_p->name`
        * do the same for `monster_p->year` as for `monster_p->name`, except
        *  that you'll (a) use atoi() (see the writeup) to convert `token` to
        *  an int before assigning it and (b) call free() on `token`
        *  afterwards: We're keeping the int, not the token.
        * do the same for `monster_p->weakness` as for `monster_p->name`
        * do the same for `monster_p->defeatedBy` as for `monster_p->name`
        * do the same for `monster_p->rating` as for `monster_p->year`,
        *  except that (a) the delimiter will be '\n' instead of ',' and
        *  (b) you'll use atof() (see below) to convert `token` to a
        *  double before assigning it
        * return a 1 (i.e. success) to the caller
        */

        char *token = fscanToken(f_p,',');

        if (token == NULL)
        {
                return 0;
        }
        monster_p->name = token;

        token = fscanToken(f_p,',');
        if (token == NULL)
        {
                return 0;
        }
        monster_p->film = token;
        
        token = fscanToken(f_p,',');
        if (token == NULL)
        {
                return 0;
        }
        monster_p->year = atoi(token);
        free(token);

        token = fscanToken(f_p,',');
        if (token == NULL)
        {
                return 0;
        }
        monster_p->weakness = token;
        
        token = fscanToken(f_p,',');
        if (token == NULL)
        {
                return 0;
        }
        monster_p->defeatedBy = token;

        token = fscanToken(f_p,'\n');
        if (token == NULL)
        {
                return 0;
        } 
        monster_p->rating = atof(token);
        free(token);

        return 1;
    }

static char *fscanToken(FILE *f_p, char delimiter)
    {
       int lenStr=0;
       char ch=0;

       char *str = (char*)malloc(1);
       strcpy(str,"\0");

        for(;;)
        {
            ch=getc(f_p);

            if(ch == EOF || ch == ',' || ch == '\n')
            {
                break;
            }

            lenStr++;
            char *newStr = (char*)malloc((lenStr+1)*sizeof(char*));
            strcpy(newStr,str);
            newStr[lenStr-1]=ch;
            free(str);
            str=newStr;
        }

        if(ch == delimiter)
        {
            return str;
        }

        else
        {
            free(str);
            return NULL;
        }

    }
