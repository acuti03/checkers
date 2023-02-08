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
        }
		p->playGround[i][j].isPawn = 0;
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

	move(2, 65);
	addstr("checkers eaten: ");

	attron(COLOR_PAIR(2));
	move(4, 65);
	printw("[ B ] : %d", 12 - cntW);
	attroff(COLOR_PAIR(2));
	
	attron(COLOR_PAIR(3));
	move(5, 65);
	printw("[ W ] : %d", 12 - cntB);
	attroff(COLOR_PAIR(3));

	mvprintw(7, 65, "press a button...");
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
				attron(COLOR_PAIR(2));
				addstr("[ B ]");
				attroff(COLOR_PAIR(2));
			}
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 0){
				addstr("[///]");
			}
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 'W'){
				attron(COLOR_PAIR(3));
				addstr("[ W ]");
				attroff(COLOR_PAIR(3));
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


int eatCheck(PlayGround *p, int *rowS, int *colS, int *rowF, int *colF, char player){
	int i, j;

//	case player B
	if(player == 'B'){
		for(i = 0; i < ROW; i++){
			for(j = 0; j < COL; j++){
				if((p->playGround[i][j].checker == 'B') &&
				((p->playGround[i+1][j+1].checker == 'W' && p->playGround[i+2][j+2].checker == 0) && (j + 2 <= 7) ||
				(p->playGround[i+1][j-1].checker == 'W' && p->playGround[i+2][j-2].checker == 0) && (j - 2 >= 0))){
					*rowS = i;
					*colS = j;
					*rowF = i + 2;
					(p->playGround[i+1][j+1].checker == 'W') ? (*colF = j + 2) : (*colF = j - 2);
					(p->playGround[i+1][j+1].checker == 'W') ? (p->playGround[i+1][j+1].checker = 0) : (p->playGround[i+1][j-1].checker = 0);
					return 1;
				}
			}
		}
	}
//	case player W
	else{
		for(i = ROW - 1; i >= 0; i--){
			for(j = 0; j < COL; j++){
				if((p->playGround[i][j].checker == 'W') &&
				((p->playGround[i-1][j+1].checker == 'B' && p->playGround[i-2][j+2].checker == 0) && (j + 2 <= 7) ||
				(p->playGround[i-1][j-1].checker == 'B' && p->playGround[i-2][j-2].checker == 0 ) && (j - 2 >= 0))){
					*rowS = i;
					*colS = j;
					*rowF = i - 2;
					(p->playGround[i-1][j+1].checker == 'B') ? (*colF = j + 2) : (*colF = j - 2);
					(p->playGround[i-1][j+1].checker == 'B') ? (p->playGround[i-1][j+1].checker = 0) : (p->playGround[i-1][j-1].checker = 0);
					return 1;
				}
			}
		}
	}

	return 0;
}


void inputBox(int *rowS, int *colS, int *rowF, int *colF, char player, PlayGround *p){
	WINDOW *win;
	int i, j;
	int x, y;

	win = stdscr;

	for(i = 0; i < 25; i++){
		addstr("# ");
	}

	addstr("\n");
	getyx(win, y, x);

	if(player == 'B'){
		do{
			move(y + 1, 23);
			addstr("Insert the X value: ");
			scanw("%d", rowS);
			move(y + 2, 23);
			addstr("Insert the Y value: ");
			scanw("%d", colS);

			move(y + 3, 23);
			addstr("Select the box (X): ");
			scanw("%d", rowF);
			move(y + 4, 23);
			addstr("Select the box (Y): ");
			scanw("%d", colF);

			if((p->playGround[*rowS][*colS].checker != 'B') || 
			(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') || 
			((*colS != (*colF + 1) && *colS != (*colF - 1)))){
				clear();
				printPlayGround(p);
				inputBox(rowS, colS, rowF, colF, player, p);
			}

		}while((p->playGround[*rowS][*colS].checker != 'B') || 
		(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') || 
		((*colS != (*colF + 1) && *colS != (*colF - 1))));
	}
	else{
		do{
			move(y + 1, 23);
			addstr("Select the checker (X): ");
			scanw("%d", rowS);
			move(y + 2, 23);
			addstr("Select the checker (Y): ");
			scanw("%d", colS);

			move(y + 3, 23);
			addstr("Select the box (X): ");
			scanw("%d", rowF);
			move(y + 4, 23);
			addstr("Select the box (Y): ");
			scanw("%d", colF);

			if((p->playGround[*rowS][*colS].checker != 'W') || 
			(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') || 
			((*colS != (*colF + 1) && *colS != (*colF - 1)))){
				clear();
				printPlayGround(p);
				inputBox(rowS, colS, rowF, colF, player, p);
			}

		}while((p->playGround[*rowS][*colS].checker != 'W') || 
		(p->playGround[*rowF][*colF].checker != 0) || (p->playGround[*rowF][*colF].colour != 'B') || 
		((*colS != (*colF + 1) && *colS != (*colF - 1))));
	}
}

void makeMove(int rowS, int colS, int rowF, int colF, PlayGround *p){
	Box temp;

	temp = p->playGround[rowF][colF];
	p->playGround[rowF][colF] = p->playGround[rowS][colS];
	p->playGround[rowS][colS] = temp;
}