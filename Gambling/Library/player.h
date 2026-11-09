#ifndef PLAYER
#define PLAYER

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

int begin();

int load_game();

int save_game();

int pointer();

#endif