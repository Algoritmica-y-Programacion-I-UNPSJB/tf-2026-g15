#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "../Library/player.h"

#define SPACE 6 

typedef struct{
    bool blank[SPACE];
    int position;
    int ammo;
}Revolver;

static int choice(){
    int keyword = 0;
    int choice = 1;

    while(keyword != 13){
        printf("%c %d %c", choice == 1 ? ' ':'<', choice, choice == 5 ? ' ':'>');
        keyword = _getch();
        printf("\r");

        if(keyword == 224){
            keyword = _getch();

            //izquierda
            if(keyword == 75)
                if(choice != 1)
                    choice--;
            //Derecha
            if(keyword == 77)
                if(choice != 5)
                    choice++;
        }
    }

    return choice;
}

static int bet(int many){
    if(many < 4)
        return many * 2500;
    if(many == 4)
        return 12000;
    return 50000;
}

static int game_begin(Revolver gun){
    int mult = 0;
    int keyword = 0;

    puts("Comienze");
    while(keyword != 27){
        keyword = _getch();

        if(keyword == ' '){
            if(gun.blank[gun.position++] == false){
                puts("click...");
                printf("%d° intento\n", ++mult);

            }else{
                puts("BANG");
                return -1;
            }
        }
        
        if(keyword == 224){
            keyword = _getch();
        }

        if(gun.position == 6)
            gun.position = 0;
    }

    printf("\n%d intentos exitosos\n", mult);

    return mult;
}

void russian(Player *player){
    Revolver gun = {{false}, 0, 0};
    int amount;

    puts("====== Russian Roulette ======");
    puts("Cuantas balas?\n");

    gun.ammo = choice();

    amount = bet(gun.ammo);

    for(int i = 0; i < gun.ammo; i++){
        int random = rand() % SPACE;

        for(int i = 0; gun.blank[random] == true; i++){
            if(random != 5){
                random++;
            }else{
                random = 0;
            }

            if(i < 10){
                random = rand() % SPACE;
            }
        }

        gun.blank[random] = true;
    }

    gun.position = rand() % SPACE;

    int result = game_begin(gun);

    if(result == -1){
        player->estado = MUERTO;
        return;
    }

    result *= amount;
    printf("+%d$\n", result);
    player->wallet += result;

    return;
}
