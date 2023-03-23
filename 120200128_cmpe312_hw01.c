#include <stdio.h>
#include <stdlib.h>

// this line defines how many rows the board will have
#define boardSize 4

// this is the number of matches in the largest row
#define maxIs  ((2 * boardSize) + 1)

struct board{
    int array[boardSize];
};

struct player{
    int number;
};

int main(){
    puts("hello");
    return 0;
}
