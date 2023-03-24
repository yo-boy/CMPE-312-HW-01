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

//  this will keep track of turns,
//  I chose to use just an int because-
// I don't need anything more and this makes it simpler
int player = 0;

// this function prints a board nicely
void showBoard(struct board myBoard);
// a function for a 2 player game
void startGame(struct board* myBoard);
// a function that provides a menu
void menu();
// this function decides if a move is correct or not for the bot
int goodMove(struct board, int index, int matches);
// this function asks the user for a Row to take from
int getRow();
// a function for a game against the compute
void playBot(struct board *myBoard);
// this function removes a number of matches from the chosen row
void removeMatches(struct board* myBoard, int  index, int matches);
// this function checks if any matches are left
int matchesLeft(struct board* myBoard);
// this function returns the nimSum of the game
int nimSum(struct board myBoard);
// this function fills the board with the appropriate number of matches
void generateBoard(struct board* myBoard){
    for (int i = 0; i < boardSize; i++){
        // put the number of matchsticks depending on which row it is
        myBoard->arr[i] = (2 * i) + 1;
    }
};

int main(){
    puts("hello");
    menu();
    return 0;
};

void menu(){
    // this variable tracks if the game is still being played
    int playing = 1;
    while (playing){
        struct board myBoard;
        //populate the board
        generateBoard(&myBoard);
        int choice;
        printf("[1] two players\n[2] play against computer\n[3] exit\nEnter a number: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                // start a 2 player game
                showBoard(myBoard);
                startGame(&myBoard);
                break;

            case 2:
                // start a game against the computer
                showBoard(myBoard);
                playBot(&myBoard);
                break;

            case 3:
                //exit the game by setting the variable to end
                playing = 0;
                break;

            default:
                printf("\nchoose one of the options\n");
                break;
        }
    }
}

void showBoard(struct board myBoard){
    // print each row
    for (int i = 0; i < boardSize; i++){
        // print the row number
        printf("%d" , i + 1);
        //print the appropriate number of spaces
        for (int j = maxIs - myBoard.arr[i]; j > 0; j--){
            printf(" ");
        }
        // print the 'I's for the row
        for (int j = 0; j < myBoard.arr[i]; j++){
            printf("I ");
        }
        //put each row on a different line
        printf("\n");
    }
}
