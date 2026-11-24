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

int begin(Player *player);

int load_game(Player *player);

int save_game(Player *player, int ask);

int pointer(int limit);

int ranking();

#endif