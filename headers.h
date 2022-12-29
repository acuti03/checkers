#include <stdio.h>
#include <stdlib.h>

/*
    LEGENDA:
    - COLOUR = B FOR BLACK W FOR WHITE
    - CHECKERS = B FOR BLACK W FOR WHITE
    - IS PAWN = 1 FOR YES NO FOR NOT
*/


#define RIG 8
#define COL 8

typedef struct{
    int colour;
    char checker;
    int isPawn;
} Box;

typedef struct{
    Box playGround[RIG][COL];
} PlayGround;

typedef enum{
    Win,
    InProgress,
    Lose
} Status;


void createPlayGround(PlayGround *p);
void printPlayGround(PlayGround *p);
void printInsertBox();