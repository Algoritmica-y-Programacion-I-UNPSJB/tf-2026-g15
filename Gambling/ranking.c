#include <stdio.h>
#include "Library/player.h"

static int count_player(FILE *archivo){
    int counter = 0;
    Player check;

    while(fread(&check, sizeof(Player), 1, archivo) == 1){
        counter++;
    }

    return counter;
}

int ranking(){
    FILE *archivo;
    archivo = fopen("Saves", "rb");

    if(archivo == NULL){
        printf("Hubo un error");
        return 1;
    }

    int amount = count_player(archivo);
    Player players[amount];

    for(int i = 0; i < amount; i++){
        fread(&(players[i]), sizeof(Player), 1, archivo);
    }

    fclose(archivo);

    int rank[amount], position = 1, higher = 0;

    //incializa el arreglo en un valor invalido
    for(int i = 0; i < amount; i++){
        rank[i] = -1;
    }

    for(int i = 0; i < amount; i++){
        for(int j = 0; j < i && higher == 0; j++){
            if(players[rank[j]].wallet < players[i].wallet){
                position = j;
                higher = 1;
            }
        }

        if(higher == 1){

        }else{
            rank[i] == i;
        }
    }
    
    
}
