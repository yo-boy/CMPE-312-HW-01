#include <stdio.h>
#include <stdlib.h>

// this line defines how many rows the board will have
#define boardSize 4

// this is the number of matches in the largest row
#define maxIs  ((2 * boardSize) + 1)

// the state of the board will be kept in an int array
struct board{
    int arr[boardSize];
};

// this will keep track of turns,
// I chose to use just an int because I don't need anything more and this makes it simpler
int player = 0;

// this function prints a board nicely
void showBoard(struct board *);
// a function for a 2 player game
void startGame();
// a function that provides a menu
void menu();
// this function decides if a move is correct or not for the bot
int goodMove(struct board, int, int);
// this function asks the user for a Row to take from
int getRow();
// a function for a game against the compute
void playBot();

void removeMatches(struct board* myBoard, int  index, int matches);

int matchesLeft(struct board* myBoard);

void startGame();

int nimSum(struct board myBoard);



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


