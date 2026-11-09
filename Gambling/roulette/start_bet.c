#include <stdio.h>
#include "../Library/player.h"
#include "roulette.h"
#include "start_bet.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define AMOUT 37

static void win_result(Player *player, Bet *bet, int result, enum Color *colors){
    if(result != 0){
        //even or odd
        if(result % 2 == 0){  
            player->wallet += bet->even*2;
        }else{
            player->wallet += bet->odd*2;
        }

        //color
        if(*(colors+result) == RED){
            player->wallet += bet->red*2;
        }else{
            player->wallet += bet->black*2;
        }
        
        //1-18 o 19-36
        if(result >= 1 && result <= 18){
            player->wallet += bet->onetoeighteen*2;
        }else{
            player->wallet += bet->nineteentothirtysix*2;
        }
        
        //docenas
        if(result >= 1 && result <= 12){
            player->wallet += bet->dozen.first*3;
        }else{
            if(result >= 13 && result <= 24){
                player->wallet += bet->dozen.second*3;
            }else{
                player->wallet += bet->dozen.third*3;
            }
        }

        //columna
        if(result % 3 == 0){
            player->wallet += bet->column.third*3;
        }else{
            if(result % 3 == 1){
                player->wallet += bet->column.second*3;
            }else{
                player->wallet += bet->column.first*3;
            }
        }

    }
    
    switch(bet->count){
        case 1:
            player->wallet += bet->number[result]*36;
        break;

        case 2:
            player->wallet += bet->number[result]*18;
        break;

        case 3:
            player->wallet += bet->number[result]*12;
        break;

        case 4:
        case 5:
            player->wallet += bet->number[result]*9;
        break;

        default:
            if(bet->count >= 6){
                player->wallet += bet->number[result]*6;
            }
    }

    return;
}

static void which_color(enum Color *colors, int result, char *color_result){
    switch(*(colors+result)){
        case RED:
            strcpy(color_result, "ROJO");
        break;
        case BLACK:
            strcpy(color_result, "NEGRO");
        break;
        case GREEN:
            strcpy(color_result, "VERDE");
        break;
    }
    return;
}

void start_bet(Player *player, Bet *bet){
    enum Color colors[AMOUT] = {
        GREEN, RED, BLACK, RED, BLACK, RED, BLACK, RED, BLACK, RED, BLACK, BLACK, RED,   //1ER DOCENA
               BLACK, RED, BLACK, RED, BLACK, RED, RED, BLACK, RED, BLACK, RED, BLACK,  //2DA DOCENA
               RED, BLACK, RED, BLACK, BLACK, RED, BLACK, RED, BLACK, RED, BLACK, RED   //3RA DOCENA
    };
    int result;
    char color_result[10];

    srand(time(NULL));

    result = rand() % AMOUT;
    which_color(colors, result, color_result);

    printf("Resultado: %d %s\n", result, color_result);

    win_result(player, bet, result, colors);
}