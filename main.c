#include "headers.h"


int main(){
    PlayGround playGround;
    Player player;
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
		player.colour = playerSelector(cnt);
        printPlayGround(&playGround);
        display(&playGround, player.colour);

//      if it can eat
        if(eatCheck(&playGround, &rowS, &colS, &rowF, &colF, player.colour)){
            makeMove(rowS, colS, rowF, colF, &playGround);
            printLine();
            mvprintw(22, 15, "you can eat from X: %d Y: %d to X: %d Y: %d", rowS, colS, rowF, colF);
            getch();
        }
//      if it can move
        else if(canMove(&playGround, &player)){
            inputBox(&rowS, &colS, &rowF, &colF, &player, &playGround);
            makeMove(rowS, colS, rowF, colF, &playGround);
        }
//      if it cannot do both it has lost
        else{
            player.status = Lose;
        }

//      if it can become a pawn
        pawn(&playGround, &player);

//      possibility of interrupting
        interrupt(&player);
//      see if you have won, lost or if the game should continue
	    player.status = updateStatus(&playGround, &player);

        refresh();
        cnt++;
    }while(player.status == InProgress);


	clear();
	printMessage(player);

	printw("\n\npress a button for close...");
    getch();
    endwin();
    return 0;
}