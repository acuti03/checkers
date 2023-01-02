#include "headers.h"


void createPlayGround(PlayGround *p){
    int i, j;

    for(i = 0; i < RIG; i++){
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
    }
}

void printPlayGround(PlayGround *p){
	int i, j;

	for(i = 0; i < RIG; i++){
		gotoxy(10 + j, 5 + (i * 2));
		for(j = 0; j < COL; j++){
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 'B'){
				textcolor(RED);
				printf("[ B ]");
			}
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 0){
				textcolor(WHITE);
				printf("[///]");
			}
			if(p->playGround[i][j].colour == 'B' && p->playGround[i][j].checker == 'W'){
				textcolor(BLUE);
				printf("[ W ]");
			}
			if(p->playGround[i][j].colour == 'W' && p->playGround[i][j].checker == 0){
				textcolor(WHITE);
				printf("[   ]");
			}
		}
	}
}

void printInsertBox(){
	printf("\n");
	printf("ciao");
}
