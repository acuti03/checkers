#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>


/*
    LEGENDA:
    - COLOUR = B FOR BLACK W FOR WHITE
    - CHECKERS = B FOR BLACK W FOR WHITE
    - IS PAWN = 1 FOR YES NO FOR NOT
*/


#define ROW 8
#define COL 8


typedef struct{
    char colour;
    char checker;
    int isPawn;
} Box;

typedef struct{
    Box playGround[ROW][COL];
} PlayGround;

typedef enum{
    Win,
    InProgress,
    Lose
} Status;


void createPlayGround(PlayGround *p);
void printPlayGround(PlayGround *p);
char playerSelector(int a);
void display(PlayGround *p, char player);
int eatCheck(PlayGround *p, int *rowS, int *colS, int *rowF, int *colF, char player);
void inputBox(int *rowS, int *colS, int *rowF, int *colF, char player, PlayGround *p);
void makeMove(int rowS, int colS, int rowF, int colF, PlayGround *p);