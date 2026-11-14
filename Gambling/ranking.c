#include <stdio.h>
#include <stdlib.h>
#include "Library/player.h"

static int contar(FILE *archivo){
    Player temp;
    int cantidad = 0;

    temp.name[0] = '\n';

    while(fread(&temp, sizeof(Player), 1, archivo) == 1){
        if(temp.estado == VIVO){
            cantidad++;
        }
    }

    if(temp.name[0] == '\n'){
        printf("No hay jugadores\n\n");
        return -1;
    }

    if(cantidad == 0){
        printf("No hay jugadores vivos\n\n");
        return -1;
    }
    rewind(archivo);

    return cantidad;
}

static void quick_sort(Player players[], int cantidad){   
    if(cantidad < 1)
        return;
    Player temp;
    int pivot = cantidad-1;
    int indice = 0;

    for(int i = 0; i < cantidad; i++){
        if(players[pivot].wallet < players[i].wallet){
            temp = players[i];
            players[i] = players[indice];
            players[indice] = temp;

            indice++;
        }
    }

    temp = players[pivot];
    players[pivot] = players[indice];
    players[indice] = temp;

    quick_sort(players, indice);
    quick_sort(players + indice + 1, cantidad - (indice+1));
    return;
}

int ranking(){
    FILE *archivo;

    archivo = fopen("Saves", "rb");

    if(archivo == NULL){
        printf("hubo un error\n");
        return 1;
    }

    int cantidad = contar(archivo);

    if(cantidad == -1){
        fclose(archivo);
        return 0;
    }

    Player *players = (Player*)malloc(sizeof(Player) * cantidad);

    for(int i = 0; fread(&players[i], sizeof(Player), 1, archivo) == 1 && i < cantidad;){
        if(players[i].estado == VIVO)
            i++;
    }

    fclose(archivo);

    quick_sort(players, cantidad);

    printf("\n\n======== Ranking ========\n");

    int posicion = 1;

    printf("1. %s | %llu", players[0].name, players[0].wallet);

    for(int i = 1; i < cantidad; i++){
        if(players[i].wallet == players[i-1].wallet){
            printf("; %s | %llu", players[i].name, players[i].wallet);
        }else{
            posicion = i+1;
            printf("\n");
            printf("%d. %s | %llu",posicion, players[i].name, players[i].wallet);
        }
    }

    printf("\n\n");
    return 0;
}
