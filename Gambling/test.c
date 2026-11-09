#include <stdio.h>
#include <string.h>

#define MAX 30

enum Estado{
    VIVO,
    MUERTO
};
typedef struct{
    char name[MAX];
    unsigned long long int wallet;
    enum Estado estado;
}Player;

int main(){
    Player player[2] = {{"Gianella", 10000ULL, VIVO}, {"Juan", 0ULL, MUERTO}};
    int coincidencia = 0, posicion = 0;

    FILE *archivo;
    archivo = fopen("Saves", "rb+");

    if(archivo == NULL){
        printf("Hubo un error al abrir el archivo");
        return 1;
    }

    while(fread(&player[1], sizeof(Player), 1, archivo) == 1 && coincidencia == 0){
        posicion++;
        if(strcmp(player[1].name, player[0].name) == 0){
            coincidencia = 1;
            posicion--;
        }
    }

    if(coincidencia == 1){
        fseek(archivo, sizeof(Player) * posicion, SEEK_SET);

        fwrite(&player[0], sizeof(Player), 1, archivo);
    }else{
        fwrite(&player[0], sizeof(Player), 1, archivo);
        fwrite(&player[1], sizeof(Player), 1, archivo);
    }

    
    fclose(archivo);
    return 0;
}