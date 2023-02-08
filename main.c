#include "functions.c"


int main(){
    PlayGround playGround;
    Status status = InProgress;
    char player;
    int rowS, colS, rowF, colF;
    int cnt = 2;


//  initialise ncurses and colors
    initscr();
    start_color();

//  generate the playground
    createPlayGround(&playGround);

//  cycle for game
    do{
        clear();
        player = playerSelector(cnt);
        printPlayGround(&playGround);

        if(eatCheck(&playGround, &rowS, &colS, &rowF, &colF, player)){
            makeMove(rowS, colS, rowF, colF, &playGround);
            printw("you can eat from X: %d Y: %d to X: %d Y: %d", rowS, colS, rowF, colF);
            getch();
        }
        else{
            inputBox(&rowS, &colS, &rowF, &colF, player, &playGround);
            makeMove(rowS, colS, rowF, colF, &playGround);
        }
        
        display(&playGround, player);
        getch();
        refresh();
        cnt++;
    }while(status == InProgress); // status == INPROGRESS


    getch();
    endwin();
    return 0;
}