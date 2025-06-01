/*
 attribute      type            definition

 name           char [15]       the monster's name
 film           char [50]       the (first) film they appeared in
 year           int             what year the film came out
 weakness       char [25]       what defeated them
 defeated by    char [30]       who defeated them
 rating         double          the film's Internet Movie Database rating
 */


#include <stdio.h>
#include <string.h>

#define NAME_SIZE 15
#define FILM_SIZE 50
#define WEAKNESS_SIZE 25
#define DEFEATEDBY_SIZE 30

typedef struct {
    
    char name[NAME_SIZE];
    char film[FILM_SIZE];
    int year;
    char weakness[WEAKNESS_SIZE];
    char defby[DEFEATEDBY_SIZE];
    double rating;
    
} Monster;

Monster monsters[] = {
    
    {
        .name="Count Dracula",
        .film="Dracula",
        .year=1931,
        .weakness="Wooden Stake",
        .defby="Van Helsing",
        .rating=7.6,
    },
    {
        .rating=8.0,
        .film="Frankenstein",
        .weakness="Fire",
        .name="The Monster",
        .year=1931,
        .defby="Villagers",
    },
    {
        .name="Voldermort",
        .film="Harry Potter",
        .year=1997,
        .weakness="Expelliarmus",
        .defby="Harry Potter",
        .rating=7.6,
    },
    {""}};
    
    
void monster_print(Monster monster)
{
    int colonIndent = 15;
    
    printf("%*s: %s\n", colonIndent, "Name", monster.name);
    printf("%*s: %s\n", colonIndent, "Film", monster.film);
    printf("%*s: %d\n", colonIndent, "Year", monster.year);
    printf("%*s: %s\n", colonIndent, "Weakness", monster.weakness);
    printf("%*s: %s\n", colonIndent, "Defeated By", monster.defby);
    printf("%*s: %.1lf\n", colonIndent, "Rating", monster.rating);

}

int main(void)
{
    for (int i=0; i<3;i++)
    {
        if (monsters[i].name[0] !=0)
        {
            monster_print(monsters [i]);
            printf("\n");
        }
        
    }

return 0;
}
