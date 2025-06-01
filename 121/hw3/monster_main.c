#include <stdio.h>
#include <string.h>

#define NAME_SIZE 15

typedef struct monster {
    char name[NAME_SIZE];
    char film[NAME_SIZE];
    int year;
    char weakness[NAME_SIZE];
    char defeatedBy[NAME_SIZE];
    double rating;
} Monster;

Monster monsters[] = {
    {

        "Count Dracula",
        "Dracula",
        1931,
        "wooden stake",
        "Van Helsing",
        7.6,
    },
    {
        .rating=8.0,
        .film="Frankenstein",
        .weakness="fire",
        .name="The Monster",
        .year=1931,
        .defeatedBy="villagers",
    },
    {'\0'},
};

void monster_printHtmlTableHeader(FILE *fptr)
{
    fprintf(fptr,"<div class='rTableRow'>\n");
    fprintf(fptr,"<div class='rTableCell'><strong>Name</strong></div>\n");
    fprintf(fptr,"<div class='rTableCell'><strong>Film</strong></div>\n");
    fprintf(fptr,"<div class='rTableCell'><strong>Year</strong></div>\n");
    fprintf(fptr,"<div class='rTableCell'><strong>Weakness</strong></div>\n");
    fprintf(fptr,"<div class='rTableCell'><strong>Defeatedby</strong></div>\n");
    fprintf(fptr,"<div class='rTableCell'><strong>Rating</strong></div>\n");
    fprintf(fptr,"</div>\n");
}

void monster_printHtmlTableRow(Monster monster,FILE *fptr)
{
    fprintf(fptr,"<div class='rTableRow'>\n");
    fprintf(fptr,"<div class='rTableCell'><strong>%s</strong></div>\n",  monster.name);
    fprintf(fptr,"<div class='rTableCell'><strong>%s</strong></div>\n",  monster.film);
    fprintf(fptr,"<div class='rTableCell'><strong>%d</strong></div>\n",  monster.year);
    fprintf(fptr,"<div class='rTableCell'><strong>%s</strong></div>\n",  monster.weakness);
    fprintf(fptr,"<div class='rTableCell'><strong>%s</strong></div>\n",  monster.defeatedBy);
    fprintf(fptr,"<div class='rTableCell'><strong>%.1lf</strong></div>\n",  monster.rating);
    fprintf(fptr,"</div>\n"); 
}

void monster_printHtmlHeader(FILE *fptr)
{
    char *string=   "<!DOCTYPE html>\n"
                    "<html>\n"
                    "<head>\n"
                    "<style>\n"
                    ".rTable {\n"
                    "display: table;\n"
                    "width: 100%;}\n"
                    ".rTableRow {\n"
                    "display: table-row;}\n"
                    ".rTableCell {\n"
                    "display: table-cell;\n"
                    "padding: 3px 10px;\n"
                    "border: 1px solid #999999;}\n"
                    "</style>\n"
                    "</head>\n"
                    "<body>\n";
    
    fprintf(fptr,"%s",string);
}
void monster_printHtmlBottom(FILE *fptr)
{
    fprintf(fptr,"</body>\n");
    fprintf(fptr,"</html>\n");
}



int main(void)
{
    FILE *fptr;
    fptr= fopen("mnstr.html", "w");
    
    int i=0;
    
    monster_printHtmlHeader(fptr);

    fprintf(fptr,"<div class=\"rTable\">");
    

    monster_printHtmlTableHeader(fptr);
    
    
    while(monsters[i].name[0] != '\0')
    {
        monster_printHtmlTableRow(monsters[i++],fptr);
    }
    
    fprintf(fptr,"</div>\n");

    monster_printHtmlBottom(fptr);

    fclose(fptr);

    return 0;
}