#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MONSTERS 1024
#define NAME_SIZE 15

typedef struct monster {
    char name[NAME_SIZE];
    char film[NAME_SIZE];
    int year;
    char weakness[NAME_SIZE];
    char defeatedBy[NAME_SIZE];
    double rating;
} Monster;

Monster monsters[MAX_MONSTERS];

void printCsvHeader(void)
/* print a CSV-compatible "monster" header to standard output */
{
   
    printf("Name,");
    printf("Film,");
    printf("Year,");
    printf("Weakness,");
    printf("DefeatedBy,");
    printf("Rating\n");
    
}

void printCsvRow(Monster monster)
/* print a CSV-compatible "monster" row to standard output */
{
    
    printf("%s", monster.name);
    printf("%s,", monster.film);
    printf("%d,", monster.year);
    printf("%s,", monster.weakness);
    printf("%s,", monster.defeatedBy);
    printf("%.1lf\n", monster.rating);
}

void saveDatabase(Monster monsters[])
{
    printCsvHeader();
    for (int i=0;i<MAX_MONSTERS;i++)
    {
        printCsvRow(monsters[i]);
    }
    
}

int foundColumnName(char columnName[], char followedBy)
{
    char buffer[2048];

    if (scanf("%[^,\n]s", buffer) != 1
        || strcmp(buffer, columnName) != 0
        || getchar() != followedBy)
    {return 0;}
    
    return 1;
}

int scanCsvHeader(void)
{
    if (!foundColumnName("Name", ','))
    {return 0;}

    if (!foundColumnName("Film", ','))
    {return 0;}
    
    if (!foundColumnName("Year", ','))
    {return 0;}
    
    if (!foundColumnName("Weakness", ','))
    {return 0;}
    
    if (!foundColumnName("Defeated by", ','))
    {return 0;}
    
    if (!foundColumnName("Rating", '\n'))
    {return 0;}
                         
    return 1;
}

int scanCsvRow(Monster *monster)
{
    if (scanf("%[^,\n]s", monster->name) != 1)
    {return 0;}

    getchar();

    if (scanf("%[^,\n]s", monster->film) != 1)
    {return 0;}
    
    getchar();
    
    if (scanf("%d", &monster->year) != 1)
    {return 0;}
    
    getchar();
    
    if (scanf("%[^,\n]s", monster->weakness) != 1)
    {return 0;}
    
    getchar();
    
    if (scanf("%[^,\n]s", monster->defeatedBy) != 1)
    {return 0;}
    
    getchar();
    
    if (scanf("%lf", &monster->rating) != 1)
    {return 0;}
    
    getchar();
    
    return 1;
}

int loadDatabase(void)
{
    int count=0;
    int result=1;
    
    if (scanCsvHeader() !=1)
    {
        return 0;
    }

    while (result == 1) //scanCsvRow(&monsters[count]) != EOF???
    {
        scanCsvRow(&monsters[count]);
        count ++;
    }
    //count ++;
    monsters[count].name[0] = '\0';

    return count;
}

int compareMonstersByYear(const void *monster0_vp, const void *monster1_vp)
{

    const Monster *monster0_p = monster0_vp;
    const Monster *monster1_p = monster1_vp;

    return monster0_p->year - monster1_p->year;
}

int main(void)
{
    int monsterCount;
    
    monsterCount = loadDatabase();
    
    if (monsterCount > 0)
    {
        qsort(monsters, monsterCount, sizeof(monsters),
        compareMonstersByYear);
        saveDatabase(monsters);
    }

    return 0;
}
