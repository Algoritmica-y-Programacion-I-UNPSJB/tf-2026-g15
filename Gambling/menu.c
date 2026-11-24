#include <stdio.h>
#include "Library/menu.h"
#include "Library/player.h"
#include "Library/games.h"

static int mostrar_menu(void){
    puts(" Jugar");
    puts(" Ranking");
    puts(" Guardar juego");
    puts(" Cargar juego");
    puts(" Salir");

    int option = pointer(5);

    return option;
}

static void mostrar_juegos(Player *player){
    printf("\nDinero actuales: %llu\n", player->wallet);
    puts("Elija el juego:\n");

    puts(" Ruleta");
    puts(" Ruleta Rusa");
    puts(" Volver");

    int option = pointer(3);

    printf("\n");

    switch(option){
        case 0:
            roulette(player);
            return;
        case 1:
            russian(player);
            return;

        default:
            return;
    }
}

int menu(Player *player){
    puts("\n====== CASINO ======");
    printf("Bienvenido %s\n", player->name);

    while(1){
        switch(mostrar_menu()){
            case 0:
                mostrar_juegos(player);
                save_game(player, 0);
                
                if(player->estado == MUERTO)
                    return 1;
                return 0;
            
            case 1:
                ranking();
                break;

            case 2:
                save_game(player, 1);
                return 0;

            case 3:
                if(load_game(player) == 1){
                    return 1;
                }
                return 0;

            case 4:  //Salir
                save_game(player, 1);
                puts("See you next time :)");
                return 1;
        }
    }
}