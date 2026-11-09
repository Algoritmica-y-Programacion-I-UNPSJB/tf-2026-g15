#include <stdio.h>
#include "../Library/player.h"
#include "roulette.h"

void bettozero(Bet *bet, int *amount_bet){
    bet->total = 0;

    bet->dozen.first = 0;
    bet->dozen.second = 0;
    bet->dozen.third = 0;
    bet->column.first = 0;
    bet->column.second = 0;
    bet->column.third = 0;

    bet->onetoeighteen = 0;
    bet->nineteentothirtysix = 0;
    bet->odd = 0;
    bet->even = 0;
    bet->red = 0;
    bet->black = 0;

    for(int i = 0; i < AMOUT; i++){
        bet->number[i] = 0;
    }
    *amount_bet = 0;
    bet->count = 0;

    return;
}

void bet_number(int *user, Bet *bet, int *amount_bet, int *monto){
    printf("Elija un numero del 0-36\n>");
    scanf("%d", user);

    if(*user >= 0 && *user <= 36){
        printf("%d$ al %d\n", *monto, *user);
        printf("apuesta concretada\n");

        bet->number[*user] += *monto;
        bet->total += *monto;
        bet->count++;
        (*amount_bet)++;
    }else{
        printf("Numero invalido\n");
    }

    return;
}

void bet_even(int *user, Bet *bet, int *amount_bet, int *monto){
    bet->even += *monto;
    bet->total += *monto;
    (*amount_bet)++;

    return;
}

void bet_odd(int *user, Bet *bet, int *amount_bet, int *monto){
    bet->odd += *monto;
    bet->total += *monto;
    (*amount_bet)++;

    return;
}

void bet_dozens(int *user, Bet *bet, int *amount_bet, int *monto){
    
    printf("A que dozena desea apostar?\n");
    printf("1. 1ra (1-12)\n");
    printf("2. 2da (13-24)\n");
    printf("3. 3ra (25-36)\n>");
    scanf("%d", user);

    switch(*user){
        case 1:
            bet->dozen.first += *monto;
            (*amount_bet)++;
        break;

        case 2:
            bet->dozen.second += *monto;
            (*amount_bet)++;
        break;

        case 3:
            bet->dozen.third += *monto;
            (*amount_bet)++;
        break;

        default:
            printf("opcion invalida\n");
            return;
    }
    bet->total += *monto;

    return;
}

void bet_columns(int *user, Bet *bet, int *amount_bet, int *monto){
    printf("A que columna queres apostar?\n");
    printf("1. 1ra (3 6 9 12 15 18 21 24 27 30 33 36)\n");
    printf("2. 2da (2 5 8 11 14 17 20 23 26 29 32 35)\n");
    printf("3. 3ra (1 4 7 10 13 16 19 22 25 28 31 34)\n>");
    scanf("%d", user);

    switch(*user){
        case 1:
            bet->column.first += *monto;
            (*amount_bet)++;
        break;

        case 2:
            bet->column.second += *monto;
            (*amount_bet)++;
        break;

        case 3:
            bet->column.third += *monto;
            (*amount_bet)++;
        break;

        default:
            printf("opcion invalida\n");
            return;
    }
    bet->total += *monto;

    return;
}

void bet_color(int *user, Bet *bet, int *amount_bet, int *monto){
    printf("A que color desea apostar?\n");
    printf("1. Rojo\n");
    printf("2. Negro\n>");
    scanf("%d", user);

    switch(*user){
        case 1:
            bet->red += *monto;
            (*amount_bet)++;
        break;

        case 2:
            bet->black += *monto;
            (*amount_bet)++;
        break;
            
        default:
            printf("opcion invalida\n");
            return;
    }

    bet->total += *monto;
    return;
}

void bet_onetoeighteen(int *user, Bet *bet, int *amount_bet, int *monto){
    bet->onetoeighteen += *monto;
    bet->total += *monto;
    (*amount_bet)++;

    return;
}

void bet_nineteentothirtysix(int *user, Bet *bet, int *amount_bet, int *monto){
    bet->nineteentothirtysix += *monto;
    bet->total += *monto;
    (*amount_bet)++;

    return;
}