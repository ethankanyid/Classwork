#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdlib.h>

#include "tic_tac_toe.h"

void printBoard(Board board)
{
    for (int row = 0; row < board.size; row++)
    {
        printf("| ");
        for (int column = 0; column < board.size; column++)
        {
            printf("%c | ", board.cells[row][column].symbol);
        }
        printf("\n");
    }
    printf("\n");
}

Cell initializeCell(char sym, int isOccupied)
{
    Cell Thing;
    Thing.symbol=sym;
    Thing.occupied=isOccupied;
    return Thing;
}

void getPosition(Board board, int pos[2])
{
    int r, c;
    do
    {
        printf("Enter the row and column: ");
        scanf("%d%d", &r, &c);
    } while (r>2 || r<0 || c>2 || c<0 || board.cells[r][c].occupied==1);
    pos[0] = r;
    pos[1] = c;
}

Board updateBoard(int r, int c, Board board)
{
    board.cells[r][c].occupied=1;
    board.counter++;
    if (board.currentPlayer == 0)
        board.cells[r][c].symbol = 'O';
    else
        board.cells[r][c].symbol = 'X';
    return board;
}

int isWinningMove(int r, int c, Board board)
{
    int possibleWin = 0;
    char playerSymbol;
    if (board.currentPlayer == 0)
        playerSymbol='O';
    else
        playerSymbol='X';
    for (int column = 0; column < board.size; column++)
    {
        if (board.cells[r][column].symbol == playerSymbol)
            possibleWin = 1;
        else
        {
            possibleWin = 0;
            break;
        }
    }
    if (possibleWin == 1)
        return possibleWin;;
    for (int row = 0; row < board.size; row++)
    {
        if (board.cells[row][c].symbol == playerSymbol)
            possibleWin = 1;
        else
        {
            possibleWin = 0;
            break;
        }
    }
    if (possibleWin)
        return possibleWin;

    if (c == r)
    {
        for (int diagonal = 0; diagonal < board.size; diagonal++)
        {
            if (board.cells[diagonal][diagonal].symbol == playerSymbol)
                possibleWin = 1;
            else
            {
                possibleWin = 0;
                break;
            }
        }
    }
    if (possibleWin==1)
        return possibleWin;

    if (c == board.size - 1 - r)
    {
        for (int otherdiagonal = 0; otherdiagonal < board.size; otherdiagonal++)
        {
            if (board.cells[otherdiagonal][board.size-1-otherdiagonal].symbol ==
                playerSymbol)
                possibleWin = 1;
            else
            {
                possibleWin = 0;
                break;
            }
        }
    }
    if (possibleWin==1)
        return possibleWin;
    return 0;
}
