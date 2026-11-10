#include <stdio.h>
#include <string.h>
#include "Library/player.h"

int ranking(){
    FILE *archivo;

    archivo = fopen("Saves", "rb");

    if(archivo == NULL){
        printf("hubo un error\n");
        return 1;
    }

    Player temp = {"\n", 0, MUERTO};
    int rank = 1;

    printf("--------Ranking--------\n"); 

    //Muestra el top 10
    while(rank <= 10 && fread(&temp, sizeof(Player), 1, archivo) != EOF){
        if(temp.estado == VIVO){
            printf("%d| %s %llu$\n", rank++, temp.name, temp.wallet);
        }
    }

    fclose(archivo);

    if(strcmp(temp.name, "\n") == 0){
        printf("No hay jugadores\n\n");
        return 0;
    }

    if(rank == 1){
        printf("No hay jugadores vivos\n\n");
    }

    return 0;
}
