#include <stdio.h>
#include <stdlib.h>

#define BOARDSIZE 4

int board[BOARDSIZE][BOARDSIZE];
int score;

// print the board
void print_board(){
    printf("Score: %d\n", score);
    printf("\"WASD\" or direction key to control.");
    puts("");puts("");

    // board
    printf("|");
    for(int i=0; i<BOARDSIZE; i++) printf("------|");
    puts("");
    for(int i=0; i<BOARDSIZE; i++){
        printf("|");
        for(int j=0; j<BOARDSIZE; j++){
            if(board[i][j]) printf("%5d |", board[i][j]);
            else printf("      |");
        }
        puts("");
        printf("|");
        for(int j=0; j<BOARDSIZE; j++) printf("------|");
        puts("");
    }

}

int main() {
    for(int i=0; i<BOARDSIZE; i++)
        for(int j=0; j<BOARDSIZE; j++)
            board[i][j] = rand()%2048+1;
    print_board();
    return 0;
}
