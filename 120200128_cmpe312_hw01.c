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

/*
I will not use a structure to keep track of players turns,
since I find it simpler and easier to just use a boolean in the-
game functions and players don't need any data beyond-
keeping track of which turn it is
*/

// this function prints a board nicely
void showBoard(struct board myBoard);
// a function for a 2 player game
void startGame(struct board* myBoard);
// a function that provides a menu
void menu();
// this function decides if a move is correct or not for the bot
int goodMove(struct board, int index, int matches);
// this function asks the user for a Row to take from
int getRow(struct board myBoard);
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
}

int main(){
    puts("hello");
    menu();
    return 0;
}

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

int getRow(struct board myBoard){
    //we put a number that will always be bigger than the number of rows
    int row = boardSize + 1;
    //we keep asking for a row number until we get a non empty valid row
    while (row > boardSize || row < 1 || myBoard.arr[row-1] == 0){
        printf("enter which row you want to take from (has to be the number of a non empty row): ");
        scanf("%d", &row);
    }
    // then we return it -1 because the row numbers dosplayed are just visual
    // and are bigger by 1 than the real index
    return row - 1;
}

void removeMatches(struct board* myBoard, int  index, int matches){
    myBoard->arr[index] -= matches;
    //we make sure the the number of matches in the row is at least 0
    if (myBoard->arr[index] < 0){
        myBoard->arr[index] = 0;
    }
}

int matchesLeft(struct board* myBoard){
    int sum = 0;
    for (int i = 0; i < boardSize && sum == 0; i++)
        sum += myBoard->arr[i];
    return sum;
}

int nimSum(struct board myBoard){
    int sum = 0;
    for (int i = 0; i < boardSize; i++){
        sum ^= myBoard.arr[i];
    }
    return sum;
}

void startGame(struct board* myBoard){
    // this will keep track of which player's turn it is
    int player = 0;

    while(matchesLeft(myBoard)){
        // if the player variable is 0 then it is player 1's turn if false then it is player 2's turn
        printf("player %d's turn\n", player + 1);
        //we get which row the player wants to take from
        int row = getRow(*myBoard);
        // we get the number of matches the player wants to take which must be 1 or more
        int num = -1;
        while (num < 1){
            printf("enter the number of matches to remove (at least 1): ");
            scanf("%d", &num);
        }
        // we make sure that the player only takes the number of matches that is available or less
        if (num > myBoard->arr[row]){
            num = myBoard->arr[row];
        }
        // we remove the matches
        removeMatches(myBoard, row, num);
        // and print the board after the change
        showBoard(*myBoard);
        // we echo what the player did
        printf("player %d removed %d matches from row %d\n", player + 1, num, row + 1);
        //then we flip to the other player's turn
        player = !player;
    }
    // after all the matches are taken we print that the game ended and which player won
    printf("game over!\nplayer %d won!\n\n", !player);
}

//this function provides the game with the computer
void playBot(struct board *myBoard){
    //this being 0 means it's the player's turn
    // and 1 means it's the bot's turn
    int player = 0;

    while (matchesLeft(myBoard)){
        // print who's turn it is
        if (player) {
            printf("bot's turn\n");
        } else {
            printf("your turn\n");
        }
        if (!player) {
            // player's turn
            // we ask for the row then the number of matches
            int row = getRow(*myBoard);
            int num = -1;
            while (num < 1) {
                printf("enter the number of matches to remove (at least 1): ");
                scanf("%d", &num);
            }
            // we make sure the number of matches is available and then remove them
            if (num > myBoard->arr[row]){
                num = myBoard->arr[row];
            }
            removeMatches(myBoard, row, num);
            // then we echo what the player did
            printf("you removed %d matches from row %d\n", num, row+1);
        } else {
            // variables to hold the computer's next move
            int row = 0;
            int matches = 0;
            // we loop through all of the possible moves and choose the last one that works
            for (int i = 0; i < boardSize; i++) {
                for (int j = 1; j <= myBoard->arr[i]; j++){
                    // we check if the move is good and if so we assign it to our variables
                    if (goodMove(*myBoard, row, matches)){
                        row = i;
                        matches = j;
                    }
                }
            }
            // carry out the computers move then echo the move
            removeMatches(myBoard, row, matches);
            printf("bot removed %d matches from row %d\n", matches, row);
        }
        // we print the board again after both the player's and bot's turns
        showBoard(*myBoard);
        // we switch to the next turn
        player = !player;
    }
    // after we are out of matches we print the winner
    printf("game over!\n");
    if (player){
        printf("you won!\n\n");
    } else {
        printf("the Bot won!\n\n");
    }
}

int goodMove(struct board myBoard, int index, int matches){
    myBoard.arr[index] -= matches;
    return nimSum(myBoard) == 0;
}
