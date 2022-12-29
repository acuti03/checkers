#include "headers.h"
//#include "conio.h"


int main(){
    PlayGround playGround;
    Status status = InProgress;
    int player;
    int a;

    createPlayGround(&playGround);
    printPlayGround(&playGround);
    printInsertBox();

    //do{

    //}while(status == InProgress);


    printf("\n\n");
    return 0;
    
}