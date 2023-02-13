#include "functions.c"


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

//      se puo mangiare
        if(eatCheck(&playGround, &rowS, &colS, &rowF, &colF, player.colour)){
            makeMove(rowS, colS, rowF, colF, &playGround);
            printLine();
            mvprintw(22, 15, "you can eat from X: %d Y: %d to X: %d Y: %d", rowS, colS, rowF, colF);
            getch();
        }
//      se puo mouversi
        else if(canMove(&playGround, &player)){
            inputBox(&rowS, &colS, &rowF, &colF, &player, &playGround);
            makeMove(rowS, colS, rowF, colF, &playGround);
        }
//      se non puo fare entrambi hai perso
        else{
            player.status = Lose;
        }

//      possibilita di interrompere
        interrupt(&player);
//      vede se per caso hai vinto o perso
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