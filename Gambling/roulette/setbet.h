#ifndef SETBET
#define SETBET

void bettozero(Bet* bet, int* amount_bet);

void bet_number(Bet* bet, int* amount_bet, int* monto);

void bet_odd(Bet* bet, int* amount_bet, int* monto);

void bet_even(Bet* bet, int* amount_bet, int* monto);

void bet_dozens(Bet* bet, int* amount_bet, int* monto);

void bet_columns(Bet* bet, int* amount_bet, int* monto);

void bet_color(Bet* bet, int* amount_bet, int* monto);

void bet_onetoeighteen(Bet* bet, int* amount_bet, int* monto);

void bet_nineteentothirtysix(Bet* bet, int* amount_bet, int* monto);

#endif