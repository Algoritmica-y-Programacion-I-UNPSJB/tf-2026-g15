#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "Library/player.h"

static void State(Player *player, char *life){
    if(player->estado == VIVO){
        strcpy(life, "Vivo");
    }else{
        strcpy(life, "Muerto");
    }

    return;
}

int pointer(int limite){
    int option = 0;
    int keyword = 0;

    printf("\033[%dA\r", limite);

    while(keyword != 13){

        for(int i = 0; i < limite; i++){
            printf(option == i ? ">" : " ");
            printf("\n");
        }

        keyword = _getch();

        if(keyword == 224){
            printf("\033[%dA\r", limite);
            keyword = _getch();

            //tecla arriba
            if(keyword == 72)
                option--;
            //tecla abajo
            if(keyword == 80)
                option ++;
        
        }

        //limites de las opciones
        if(option < 0)
            option = limite-1;

        if(option >= limite)
            option = 0;
    
    }
    return option;
}

static void new_game(Player *player){
    printf("elija un nombre:\n>");

    fgets(player->name, sizeof(player->name), stdin);
    player->name[strcspn(player->name, "\n")] = '\0';

    player->estado = VIVO;
    player->wallet = 1000;

    while (save_game(player, 1) == 2){
        printf("Elija otro nombre\n>");

        fgets(player->name, sizeof(player->name), stdin);
        player->name[strcspn(player->name, "\n")] = '\0';
    }

    return;
}

int load_game(Player *player){
    FILE *archivo;
    archivo = fopen("Saves", "rb+");

    char life[7];

    if(archivo == NULL){
        printf("Hubo un error al abrir el archivo\n");
        return 1;
    }

    if(fread(player, sizeof(Player), 1, archivo) != 1){
        printf("No hay partidas guardadas\n");
        fclose(archivo);
        new_game(player);
        return 0;
    }

    while(1){
        int counter = 0;  
        //counter es la cantidad de partidas guardadas

        printf("\nPartidas guardadas:\n");
        printf("Nombre |Billetera |Estado\n");

        rewind(archivo);
        
        while(fread(player, sizeof(Player), 1, archivo) == 1){
            State(player, life);
            counter++;

            printf(" %s |%llu$ | %s\n", player->name, player->wallet, life);

        }

        int option = pointer(counter);

        fseek(archivo, sizeof(Player) * option, SEEK_SET);
        fread(player, sizeof(Player), 1, archivo);

        if(player->estado == MUERTO){
            printf("Este jugador esta muerto -_-\n");
            printf("Que desafortunado\n");

        }else{
            printf("\nPartida cargada exitosamente\n\n");
            fclose(archivo);
            return 0;
        }
    }
}

int save_game(Player *player, int ask){
    Player check;
    FILE *archivo;
    archivo = fopen("Saves", "rb+");
    int exist = 0, position = 0;

    if(archivo == NULL){
        printf("Hubo un error\n");
        return 1;
    }

    while(fread(&check, sizeof(Player), 1, archivo) == 1 && exist == 0){
        position++;

        if(strcmp(check.name, player->name) == 0){
            exist = 1;
            position--;

        }

    }

    if(exist == 1){
        if(ask == 1){

            printf("\nEl nombre %s ya esta registrado\n", player->name);
            printf("Quiere sobreescribir los datos?\n");

            printf(" s\n");
            printf(" n\n");
            int option = pointer(2);

            switch(option){
                case 0:
                    fseek(archivo, sizeof(Player) * position, SEEK_SET);
                    fwrite(player, sizeof(Player), 1, archivo);

                    printf("Se sobreescribieron los datos\n");

                    fclose(archivo);
                    return 0;

                case 1:
                    fclose(archivo);
                    return 2;
            }
        }else{
            fseek(archivo, sizeof(Player) * position, SEEK_SET);
            fwrite(player, sizeof(Player), 1, archivo);
        }

    }else{
        fwrite(player, sizeof(Player), 1, archivo);

    }

    fclose(archivo);
    return 0;
}

int begin(Player *player){
    printf(" iniciar nuevo juego\n");
    printf(" cargar partida\n");

    int option = pointer(2);

    switch(option){
        case 0:
            new_game(player);
        break;
        
        case 1:
            load_game(player);
        break;
    }

    return 0;
}