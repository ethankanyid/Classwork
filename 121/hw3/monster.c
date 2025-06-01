#include <stdio.h>
#include <string.h>

#define NAME_SIZE 15


typedef struct {
    char name[NAME_SIZE];
    char film[NAME_SIZE];
    int year;
    char weakness[NAME_SIZE];
    char defeatedBy[NAME_SIZE];
    int rating;
} Monster;

Monster monsters[] = {
{
.name="Count Dracula",
.film="Dracula",
.year=1931,
.weakness="wooden stake",
.defeatedBy="Van Helsing",
.rating=7.6,
},
{
.rating=8.0,
.film="Frankenstein",
.weakness="fire",
.name="The Monster",
.year=1931,
.defeatedBy="villagers",
},

{
"'\0'",
},
};
void monster_print(Monster monster)
{
    int colonIndent = 15;

    printf("%*s: %s\n", colonIndent, "Name", monster.name);
    printf("%*s: %s\n", colonIndent, "Film", monster.film);
    printf("%*s: %d\n", colonIndent, "Year", monster.year);
    printf("%*s: %s\n", colonIndent, "Weakness", monster.weakness);
    printf("%*s: %s\n", colonIndent, "Defeated By", monster.defeatedBy);
    printf("%*s: %d\n", colonIndent, "Rating", monster.rating);

}
int main(void)
{

    for (int i=0;i<2;i++)
    {
        if (monsters[i].name[0] != '\0')
        {
            monster_print(monsters[i]);
        }
        printf("\n");
    }
    printf("\n");
    
    return 0;
}
