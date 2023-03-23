#include <stdio.h>
#include <stdlib.h>

// this line defines how many rows the board will have
#define boardSize 4

// this is the number of matches in the largest row
#define maxIs  ((2 * boardSize) + 1)


struct board{
    int arr[boardSize];
};

struct player{
    int isTurn[0];
};

void showBoard(struct board *, struct player *);

void startGame();

void menu();

int goodMove(struct board, int, int);

void playBot();

void generateBoard(struct board* myBoard){
    for (int i = 0; i < boardSize; i++){
        // put the number of matchsticks depending on which row it is
        myBoard->arr[i] = (2 * i) + 1;
    }
};

int main(){
    puts("hello");
    return 0;
};


