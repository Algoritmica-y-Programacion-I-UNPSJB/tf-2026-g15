#include <stdio.h>
#include "Library/menu.h"
#include "Library/player.h"
#include "Library/games.h"

static int mostrar_menu(void){
    printf(" Jugar\n");
    printf(" Guardar juego\n");
    printf(" Cargar juego\n");
    printf(" Salir\n");

    int option = pointer(4);

    return option;
}

static void mostrar_juegos(Player *player){
    printf("\nDinero actuales: %llu\n", player->wallet);
    printf("Elija el juego:\n");

    printf(" Ruleta\n");
    printf(" Volver\n");

    int option = pointer(2);

    printf("\n");

    switch(option){
        case 0:
            roulette(player);
            return;

        case 1:
            return;
    }
}

int menu(Player *player){
    printf("====== CASINO ======\n");
    printf("Bienvenido %s\n", player->name);

    while(1){
        switch(mostrar_menu()){
            case 0:  //Jugar
                mostrar_juegos(player);
                return 0;

            case 1:
                save_game(player, 1);
                return 0;

            case 2:
                if(load_game(player) == 1){
                    return 1;
                }
                return 0;

            case 3:  //Salir
                save_game(player, 1);
                printf("See you next time :)");
                return 1;
        }
    }
}