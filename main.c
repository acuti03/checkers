#include "functions.c"


int main(){
    PlayGround playGround;
    Status status = InProgress;
    int player;
    int a;

    system("clear");
    createPlayGround(&playGround);
    printPlayGround(&playGround);
    printInsertBox();

    //do{

    //}while(status == InProgress);


    printf("\n\n");
    return 0;
    
}