#include <stdio.h>
#include "../Library/player.h"
#include "../Library/games.h"
#include "roulette.h"
#include "setbet.h"
#include "start_bet.h"

static void show_roulette(){

    printf("______________________________________________\n");
    printf("|  |3 6 9 12 15 18 21 24 27 30 33 36 |2:1 3ro|\n");
    printf("|0 |2 5 8 11 14 17 20 23 26 29 32 35 |2:1 2do|\n");
    printf("|  |1 4 7 10 13 16 19 22 25 28 31 34 |2:1 1ro|\n");
    printf("|==|========|===========|============|=======|\n");
    printf("   |1er 12na| 2da 12na  | 3ra 12na   |-------|\n");
    printf("   |1-18 | PAR | NEGRO | ROJO | IMPAR | 19-36|\n");
    printf("   |=========================================|\n");

    return;
}

static void show_rules(){
    puts("\n========== REGLAS DE LA RULETA ==========");
    puts("1. Elegi uno o varios tipos de apuesta y asignales un monto.");
    puts("2. La suma de las apuestas no puede superar tu saldo.");
    puts("3. No podes iniciar una ronda sin haber apostado.");
    puts("4. La ruleta elige al azar un numero entre 0 y 36.");
    puts("5. El 0 es verde: no gana par/impar, color, rangos, docenas ni columnas.");
    puts("\nPagos:");
    puts("- Par, impar, rojo, negro, 1-18 y 19-36: pagan 2 veces la apuesta.");
    puts("- Docenas y columnas: pagan 3 veces la apuesta.");
    puts("- Numero especifico: paga segun la cantidad de numeros apostados.");
    puts("  1 numero: x36 | 2: x18 | 3: x12 | 4-5: x9 | 6 o mas: x6.");

    return;
}

typedef void (*apuestas)(Bet*, int*, int*);

static void init_bet(int *user, Player *player, Bet *bet, int *amount_bet){
    if(*user == 8 || *user == 9)
        return;
    
    int monto = 0;
    apuestas options[] = {bet_number, bet_even, bet_odd, bet_dozens, bet_columns, bet_color, bet_onetoeighteen, bet_nineteentothirtysix};

    printf("Saldo: %llu$\n", player->wallet);
    printf("Cuanto desea apostar?\n>");
    scanf("%d", &monto);

    if(monto < 1){
        printf("No\n");
        return;
    }

    if((monto + bet->total) <= player->wallet){
        options[*user](bet, amount_bet, &monto);
    }else{
        printf("Saldo insuficiente :(\n");
    }

    *user = 0;
    return;
}

void roulette(Player *player){
    Bet bet;

    int user = 0, amount_bet = 0;

    printf("======= Ruleta ======\n");

    show_roulette();
    
    do{
        bettozero(&bet, &amount_bet);

        printf("\nhaga su apuesta: \n");
        do{
            printf(" Numero especifico\n");
            printf(" Par\n");
            printf(" Impar\n");
            printf(" 12-nas\n");
            printf(" Columnas\n");
            printf(" color\n");
            printf(" 1-18\n");
            printf(" 19-36\n");
            printf(" iniciar\n");
            printf(" Salir\n");
            printf(" Reglas\n");

            user = pointer(11);

            if(user == 10){
                show_rules();
                user = 0;
                continue;
            }

            init_bet(&user, player, &bet, &amount_bet);

            if(user == 8 && amount_bet == 0){
                printf("No puede jugar si no hace una apuesta\n");
                user = 0;
            }

            printf("total apostado: %d$\n\n", bet.total);
        }while(user != 8 && user != 9);

        if(user == 8){
            player->wallet -= bet.total;
            start_bet(player, &bet);
        }

        printf("Saldo: %llu$\n", player->wallet);
        save_game(player, 0);
        bettozero(&bet, &amount_bet);
        
        printf("=================================================================\n");
    }while(user != 9);

    printf("Bye Bye\n\n");
    return;
}
