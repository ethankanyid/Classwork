#include <stdio.h>
#include <assert.h> // for assert()
#include <ctype.h>
#include <stdbool.h>

struct CodeStats
{
    int lineCount;
    int linesWithCodeCount;
    int cplusplusCommentCount;
    int cCommentCount;
    int cPPDCount;
};


void codeStats_init(struct CodeStats *codeStats)
{
    codeStats->lineCount = 0;
    codeStats->linesWithCodeCount = 0;
    codeStats-> cplusplusCommentCount = 0;
    codeStats->cCommentCount = 0;
    codeStats->cPPDCount = 0;
}


void codeStats_print(struct CodeStats codeStats, char *fileName)
{
    printf("                       file: %s\n", fileName);
    printf("                 line count: %d\n", codeStats.lineCount);
    printf("      lines with code count: %d\n", codeStats.linesWithCodeCount);
    printf("         cpp comments count: %d\n", codeStats.cplusplusCommentCount);
    printf("           c comments count: %d\n", codeStats.cCommentCount);
    printf(" c pre-processor directives: %d\n", codeStats.cPPDCount);
}


void codeStats_accumulate(struct CodeStats *codeStats, char *fileName)
{
    FILE *f = fopen(fileName, "r");
    int ch;

    enum
    {
        START,
        FOUND_COMMENT,
        IS_CPP_COMMENT,
        IS_C_COMMENT,
        FOUND_STRING,
        ESCAPE_STRING,
        FOUND_CHAR,
        ESCAPE_CHAR,
        FOUND_PPD,
        ESCAPE_PPD
    } state = START;

    assert(f);

    int foundCodeOnLine = 0;
    int foundComment = 0;
    int foundPPD = 0;

    while ((ch = getc(f)) != EOF)
    {
        switch (state)
        {
        case START:
            if (ch == '/')
                state = FOUND_COMMENT;
            else if (ch == '\"')
                state = FOUND_STRING;
            else if (ch == '\'')
                state = FOUND_CHAR;
            else if (ch == '#')
            {
                state = FOUND_PPD;
                foundPPD = 1;
            }
            else if (ch == '\n')
            {
                codeStats->lineCount++;
                codeStats->linesWithCodeCount += foundCodeOnLine;
                foundCodeOnLine = 0;
            }
            else if (!foundCodeOnLine && !isspace(ch))
                foundCodeOnLine = 1;

            break;
        case FOUND_COMMENT:
            if (ch == '/')
            {
                state = IS_CPP_COMMENT;
                foundComment = 1;
                break;
            }
            else if (ch == '*')
            {
                state = IS_C_COMMENT;
                foundComment = 1;
                break;
            }
            else if (!foundCodeOnLine && !isspace(ch))
                foundCodeOnLine = 1;

            state = START;
            break;
        case IS_CPP_COMMENT:
            if (ch == '\n')
            {
                codeStats->lineCount++;
                codeStats->linesWithCodeCount += foundCodeOnLine;
                foundCodeOnLine = 0;
                state = START;
            }
            codeStats->cplusplusCommentCount += foundComment;
            foundComment = 0;

            break;
        case IS_C_COMMENT:
            if (ch == '\n')
            {
                codeStats->lineCount++;
                codeStats->linesWithCodeCount += foundCodeOnLine;
                foundCodeOnLine = 0;
                state = START;
            }
            codeStats->cCommentCount += foundComment;
            foundComment = 0;

            break;
        case FOUND_STRING:
            if (ch == '\\')
                state = ESCAPE_STRING;
            else if (ch == '\"')
                state = START;
            break;
        case ESCAPE_STRING:
            if (ch == '\n')
            {
                codeStats->lineCount++;
                codeStats->linesWithCodeCount += foundCodeOnLine;
                foundCodeOnLine = 0;
            }
            state = FOUND_STRING;

            break;
        case FOUND_CHAR:
            if (ch == '\\')
            {
                state = ESCAPE_CHAR;
            }
            else if (ch == '\'')
            {
                state = START;
            }
            break;
        case ESCAPE_CHAR:
            if (ch == '\n')
            {
                codeStats->lineCount++;
                codeStats->linesWithCodeCount += foundCodeOnLine;
                foundCodeOnLine = 0;
            }
            state = FOUND_CHAR;

            break;
        case FOUND_PPD:
        //doesnt account for comments after PPD
            codeStats->cPPDCount+= foundPPD;
            if (ch == '\\')
                state = ESCAPE_PPD;
            else if (ch == '\n')
            {
                codeStats->lineCount++;
                codeStats->linesWithCodeCount += foundCodeOnLine;
                foundCodeOnLine = 0;
                state = START;
            }
            foundPPD = 0;
            break;
        case ESCAPE_PPD:
            if (ch == '\n')
            {
                codeStats->lineCount++;
                codeStats->linesWithCodeCount += foundCodeOnLine;
                foundCodeOnLine = 0;
            }
            state = FOUND_PPD;

            break;
        default:
            assert(0);
            break;
        }
    }
    fclose(f);
    assert(state == START);
}


int main(int argc, char *argv[])
{
    struct CodeStats codeStats;
    int i;

    for (i = 1; i < argc; i++)
    {
        codeStats_init(&codeStats);
        codeStats_accumulate(&codeStats, argv[i]);
        codeStats_print(codeStats, argv[i]); // no "&" -- see why?
        if (i != argc-1)   // if this wasn't the last file ...
            printf("\n");  // ... print out a separating newline
    }
    return 0;
}
