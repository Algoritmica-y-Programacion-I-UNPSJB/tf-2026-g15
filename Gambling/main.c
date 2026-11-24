#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Library/menu.h"
#include "Library/player.h"

int main(){
    Player player;
    srand(time(NULL));
    
    system("cls");

    while(begin(&player) == 1);

    while(menu(&player) == 0);

    return 0;
}