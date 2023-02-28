#include "headers.h"


char playerSelector(int a){
	return (a % 2 == 0) ? ('W') : ('B');
}


void createPlayGround(PlayGround *p){
    int i, j;

    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            if(i < 3){
                if((i + j) % 2 == 0){
                    p->playGround[i][j].colour = 'B';
					p->playGround[i][j].checker = 'B';
                }
				else{
					p->playGround[i][j].colour = 'W';
					p->playGround[i][j].checker = 0;
				}
            }
			else if(i > 2 && i < 5){
				if((i + j) % 2 == 0){
					p->playGround[i][j].colour = 'B';
				}
				else{
					p->playGround[i][j].colour = 'W';
				}
				p->playGround[i][j].checker = 0;
			}
			else{
				if((i + j) % 2 == 0){
					p->playGround[i][j].colour = 'B';
					p->playGround[i][j].checker = 'W';
				}
				else{
					p->playGround[i][j].colour = 'W';
					p->playGround[i][j].checker = 0;
				}
			}
			p->playGround[i][j].isPawn = false;
        }
    }
}


void display(PlayGround *p, char player){
	int i, j;
	int cntB = 0, cntW = 0;

	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			if(p->playGround[i][j].checker == 'B'){
				cntB++;
			}
			if(p->playGround[i][j].checker == 'W'){
				cntW++;
			}
		}
	}

	(player == 'W') ? (mvprintw(2, 65, "It's W's turn")) : (mvprintw(2, 65, "It's B's turn"));


	move(4, 65);
	addstr("checkers eaten: ");

	attron(COLOR_PAIR(2));
	move(5, 65);
	printw("[ B ] : %d", 12 - cntW);
	attroff(COLOR_PAIR(2));
	
	attron(COLOR_PAIR(3));
	move(6, 65);
	printw("[ W ] : %d", 12 - cntB);
	attroff(COLOR_PAIR(3));

	//mvprintw(5, 65, "press a button...");
}


void printNumber(){
	int i;

	move(2, 15);

	for(i = 0; i < ROW; i++){
		printw("%d     ", i);
	}
}


void printPlayGround(PlayGround *p){
	int i, j = 0;
	WINDOW *win;
	int x, y;

	win = stdscr;
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	attron(COLOR_PAIR(1));

	printNumber();

	attroff(COLOR_PAIR(1));

	move(4, 10);

	for(i = 0; i < ROW; i++){
		attron(COLOR_PAIR(1));
		printw("%d  ", i);
		attroff(COLOR_PAIR(1));
		for(j = 0; j < COL; j++){
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 'B'){
				if(p->playGround[i][j].isPawn == false){
					attron(COLOR_PAIR(2));
					addstr("[ B ]");
					attroff(COLOR_PAIR(2));
				}
				else{
					attron(COLOR_PAIR(2));
					addstr("[B B]");
					attroff(COLOR_PAIR(2));
				}
			}
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 0){
				addstr("[///]");
			}
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 'W'){
				if(p->playGround[i][j].isPawn == false){
					attron(COLOR_PAIR(3));
					addstr("[ W ]");
					attroff(COLOR_PAIR(3));
				}
				else{
					attron(COLOR_PAIR(3));
					addstr("[W W]");
					attroff(COLOR_PAIR(3));
				}
			}
			if(p->playGround[i][j].colour == 'W' && p->playGround[i][j].checker == 0){
				addstr("[   ]");
			}
			addstr(" ");
		}
		getyx(win, y, x);
		move(y + 2, 10);
	}
}


bool eatCheck(PlayGround *p, int *rowS, int *colS, int *rowF, int *colF, char player){
	int i, j;

//	case player B
	if(player == 'B'){
		for(i = 0; i < ROW; i++){
			for(j = 0; j < COL; j++){
				if(p->playGround[i][j].isPawn == false){
					if((p->playGround[i][j].checker == 'B') &&
					((p->playGround[i+1][j+1].checker == 'W' && p->playGround[i+2][j+2].checker == 0 && p->playGround[i+1][j+1].isPawn == false) && (j + 2 <= 7) && (i + 2 <= 7) ||
					(p->playGround[i+1][j-1].checker == 'W' && p->playGround[i+2][j-2].checker == 0 && p->playGround[i+1][j-1].isPawn == false) && (j - 2 >= 0) && (i + 2 <= 7))){
						
						*rowS = i;
						*colS = j;
						*rowF = i + 2;
						(p->playGround[i+1][j+1].checker == 'W') ? (*colF = j + 2) : (*colF = j - 2);
						(p->playGround[i+1][j+1].checker == 'W') ? (p->playGround[i+1][j+1].checker = 0) : (p->playGround[i+1][j-1].checker = 0);
						return true;
					}
				}
				else{
					if((p->playGround[i][j].checker == 'B') &&
					(((p->playGround[i+1][j+1].checker == 'W' && p->playGround[i+2][j+2].checker == 0) && (j + 2 <= 7) && (i + 2 <= 7)) ||
					((p->playGround[i+1][j-1].checker == 'W' && p->playGround[i+2][j-2].checker == 0) && (j - 2 >= 0) && (i + 2 <= 7)) ||
					((p->playGround[i-1][j+1].checker == 'W' && p->playGround[i-2][j+2].checker == 0) && (j + 2 >= 0) && (i - 2 <= 7)) ||
					((p->playGround[i-1][j-1].checker == 'W' && p->playGround[i-1][j-2].checker == 0) && (j - 2 >= 0) && (i - 2 <= 7)))){

						*rowS = i;
						*colS = j;
						if(p->playGround[i+1][j+1].checker == 'W'){ *rowF = i + 2; *colF = j + 2; p->playGround[i+1][j+1].checker = 0; }
						else if(p->playGround[i+1][j-1].checker == 'W'){ *rowF = i + 2; *colF = j - 2; p->playGround[i+1][j-1].checker = 0; }
						else if(p->playGround[i-1][j+1].checker == 'W'){ *rowF = i - 2; *colF = j + 2; p->playGround[i-1][j+1].checker = 0; }
						else { *rowF = i - 2; *colF = j - 2; p->playGround[i-1][j-1].checker = 0; }
						return true;
					}
				}
			}
		}
	}
//	case player W
	else{
		for(i = ROW - 1; i >= 0; i--){
			for(j = 0; j < COL; j++){
				if(p->playGround[i][j].isPawn == false){
					if((p->playGround[i][j].checker == 'W') &&
					((p->playGround[i-1][j+1].checker == 'B' && p->playGround[i-2][j+2].checker == 0 && p->playGround[i-1][j+1].isPawn == false) && (j + 2 <= 7) && (i - 2 >= 0) ||
					(p->playGround[i-1][j-1].checker == 'B' && p->playGround[i-2][j-2].checker == 0 && p->playGround[i-1][j-1].isPawn == false) && (j - 2 >= 0) && (i - 2 >= 0))){

						*rowS = i;
						*colS = j;
						*rowF = i - 2;
						(p->playGround[i-1][j+1].checker == 'B') ? (*colF = j + 2) : (*colF = j - 2);
						(p->playGround[i-1][j+1].checker == 'B') ? (p->playGround[i-1][j+1].checker = 0) : (p->playGround[i-1][j-1].checker = 0);
						return true;
					}
				}
				else{
					if((p->playGround[i][j].checker == 'W') &&
					(((p->playGround[i+1][j+1].checker == 'B' && p->playGround[i+2][j+2].checker == 0) && (j + 2 <= 7) && (i + 2 <= 7)) ||
					((p->playGround[i+1][j-1].checker == 'B' && p->playGround[i+2][j-2].checker == 0) && (j - 2 >= 0) && (i + 2 <= 7)) ||
					((p->playGround[i-1][j+1].checker == 'B' && p->playGround[i-2][j+2].checker == 0) && (j + 2 >= 0) && (i - 2 <= 7)) ||
					((p->playGround[i-1][j-1].checker == 'B' && p->playGround[i-1][j-2].checker == 0) && (j - 2 >= 0) && (i - 2 <= 7)))){

						*rowS = i;
						*colS = j;
						if(p->playGround[i+1][j+1].checker == 'B'){ *rowF = i + 2; *colF = j + 2; p->playGround[i+1][j+1].checker = 0; }
						else if(p->playGround[i+1][j-1].checker == 'B'){ *rowF = i + 2; *colF = j - 2; p->playGround[i+1][j-1].checker = 0; }
						else if(p->playGround[i-1][j+1].checker == 'B'){ *rowF = i - 2; *colF = j + 2; p->playGround[i-1][j+1].checker = 0; }
						else { *rowF = i - 2; *colF = j - 2; p->playGround[i-1][j-1].checker = 0; }
						return true;
					}
				}
			}
		}
	}

	return false;
}


void printLine(){
	int i;

	move(20, 10);
	for(i = 0; i < 25; i++){
		addstr("# ");
	}

	addstr("\n");
}


void interrupt(Player *p){
	WINDOW *win;
	int x, y;

	win = stdscr;
	getyx(win, y, x);

	if(p->status == Lose) return;

	mvprintw(y + 1, 22, "Do you want interrupt ? (y/n)");
	(getch() == 'y') ? (p->status = Lose) : (p->status = InProgress);
}


void inputBox(int *rowS, int *colS, int *rowF, int *colF, Player *player, PlayGround *p){
	int i, j;

	printLine();

	if(player->colour == 'B'){
		move(22, 22);
		addstr("Insert the X value: ");
		scanw("%d", rowS);
		move(23, 22);
		addstr("Insert the Y value: ");
		scanw("%d", colS);

		move(24, 22);
		addstr("Select the box (X): ");
		scanw("%d", rowF);
		move(25, 22);
		addstr("Select the box (Y): ");
		scanw("%d", colF);

		if(p->playGround[*rowS][*colS].isPawn == false){
			if((p->playGround[*rowS][*colS].checker != 'B') ||
			(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') || 
			(*colS != *colF + 1 && *colS != *colF - 1) || (*rowS != *rowF - 1)){
				clear();
				printPlayGround(p);
				display(p, player->colour);
				inputBox(rowS, colS, rowF, colF, player, p);
			}
		}
		else{
			if((p->playGround[*rowS][*colS].checker != 'B') ||
			(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') ||
			(*colS != *colF + 1 && *colS != *colF - 1) || (*rowS != *rowF - 1 && *rowS != *rowF + 1)){
				clear();
				printPlayGround(p);
				display(p, player->colour);
				inputBox(rowS, colS, rowF, colF, player, p);
			}
		}
	}
	else{
		move(22, 22);
		addstr("Select the checker (X): ");
		scanw("%d", rowS);
		move(23, 22);
		addstr("Select the checker (Y): ");
		scanw("%d", colS);

		move(24, 22);
		addstr("Select the box (X): ");
		scanw("%d", rowF);
		move(25, 22);
		addstr("Select the box (Y): ");
		scanw("%d", colF);

		if(p->playGround[*rowS][*colS].isPawn == false){
			if((p->playGround[*rowS][*colS].checker != 'W') ||
			(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') || 
			(*colS != *colF + 1 && *colS != *colF - 1) || (*rowS != *rowF + 1)){
				clear();
				printPlayGround(p);
				display(p, player->colour);
				inputBox(rowS, colS, rowF, colF, player, p);
			}
		}
		else{
			if((p->playGround[*rowS][*colS].checker != 'W') ||
			(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') ||
			(*colS != *colF + 1 && *colS != *colF - 1) || (*rowS != *rowF - 1 && *rowS != *rowF + 1)){
				clear();
				printPlayGround(p);
				display(p, player->colour);
				inputBox(rowS, colS, rowF, colF, player, p);
			}
		}
	}
}


void makeMove(int rowS, int colS, int rowF, int colF, PlayGround *p){
	Box temp;

	temp = p->playGround[rowF][colF];
	p->playGround[rowF][colF] = p->playGround[rowS][colS];
	p->playGround[rowS][colS] = temp;
}


Status updateStatus(PlayGround *p, Player *player){
	int i, j;
	int cntW = 0, cntB = 0;

	if(player->status == Lose){
		return Lose;
	}

	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			if(p->playGround[i][j].checker == 'W'){
				cntW++;
			}
			if(p->playGround[i][j].checker == 'B'){
				cntB++;
			}
		}
	}

	if(player->colour == 'W'){
		if(cntB == 0) return Win;
		if(cntW == 0) return Lose;
	}
	else{
		if(cntW == 0) return Win;
		if(cntB == 0) return Lose; 
	}

	return InProgress;
}


bool canMove(PlayGround *p, Player *player){
	int i, j;

	if(player->colour == 'B'){
		for(i = 0; i < ROW; i++){
			for(j = 0; j < COL; j++){
				if(p->playGround[i][j].isPawn == false){
					if(p->playGround[i][j].checker == 'B' &&
					((p->playGround[i+1][j+1].checker == 0 && (j + 1 <= 7) && (i + 1 <= 7)) ||
					(p->playGround[i+1][j-1].checker == 0 && (j - 1 >= 0) && (i + 1 <= 7)))){
						return true;
					}
				}
				else{
					if(p->playGround[i][j].checker == 'B' &&
					((p->playGround[i-1][j+1].checker == 0 && (j + 1 <= 7) && (i - 1 >= 0)) ||
					(p->playGround[i-1][j-1].checker == 0 && (j - 1 >= 0) && (i - 1 >= 0)) ||
					(p->playGround[i+1][j+1].checker == 0 && (j + 1 <= 7) && (i + 1 <= 7)) ||
					(p->playGround[i+1][j-1].checker == 0 && (j - 1 >= 0) && (i + 1 <= 7)))){
						return true;
					}
				}
			}
		}
	}
	else{
		for(i = ROW - 1; i >= 0; i--){
			for(j = 0; j < COL; j++){
				if(p->playGround[i][j].isPawn == false){
					if(p->playGround[i][j].checker == 'W' &&
					((p->playGround[i-1][j+1].checker == 0 && (j + 1 <= 7) && (i - 1 >= 0)) ||
					(p->playGround[i-1][j-1].checker == 0 && (j - 1 >= 0) && (i - 1 >= 0)))){
						return true;
					}
				}
				else{
					if(p->playGround[i][j].checker == 'W' &&
					((p->playGround[i-1][j+1].checker == 0 && (j + 1 <= 7) && (i - 1 >= 0)) ||
					(p->playGround[i-1][j-1].checker == 0 && (j - 1 >= 0) && (i - 1 >= 0)) ||
					(p->playGround[i+1][j+1].checker == 0 && (j + 1 <= 7) && (i + 1 <= 7)) ||
					(p->playGround[i+1][j-1].checker == 0 && (j - 1 >= 0) && (i + 1 <= 7)))){
						return true;
					}
				}
			}
		}
	}

	return false;
}


void pawn(PlayGround *p, Player *player){
	int i, j;

	if(player->colour == 'W'){
		for(i = 0, j = 0; j < COL; j++){
			if(p->playGround[i][j].checker == 'W'){
				p->playGround[i][j].isPawn = true;
			}
		}
	}
	else{
		for(i = 7, j = 0; j < COL; j++){
			if(p->playGround[i][j].checker == 'B'){
				p->playGround[i][j].isPawn = true;
			}
		}
	}
}


void printMessage(Player player){
	if(player.colour == 'W'){
        (player.status == Win) ? (printw("WINNER: PLAYER W\nLOSER: PLAYER B")) : (printw("WINNER : PLAYER B\nLOSER: PLAYER W"));
    }
    else{
        (player.status == Win) ? (printw("WINNER: PLAYER B\nLOSER: PLAYER W")) : (printw("WINNER : PLAYER W\nLOSER: PLAYER B"));
    }
}