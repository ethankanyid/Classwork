#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdlib.h>

#ifndef _INCLUDED_TIC_TAC_TOE_H
#define MAXELEMENT 3

typedef struct
{
int occupied;
char symbol;
} Cell;


typedef struct
{
Cell cells[MAXELEMENT][MAXELEMENT];
int winner;
int counter;
int size;
int currentPlayer;
} Board;


Cell initializeCell(char, int);
void getPosition(Board, int[2]);
Board updateBoard(int, int, Board);
int isWinningMove(int, int, Board);
void printBoard(Board);

#define _INCLUDED_TIC_TAC_TOE_H
#endif
