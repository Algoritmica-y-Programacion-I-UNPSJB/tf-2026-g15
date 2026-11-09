#ifndef ROULETTE
#define ROULETTE

#define AMOUT 37

enum Color{
    RED,
    BLACK,
    GREEN
};

typedef struct{
    int first;
    int second;
    int third;
}groups;

typedef struct{
    groups dozen;
    groups column;
    int red;
    int black;
    int even;
    int odd;
    int onetoeighteen;
    int nineteentothirtysix;
    int number[AMOUT];
    int count;
    int total;
}Bet;

#endif  