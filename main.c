#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define BOARDSIZE 4
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int board[BOARDSIZE][BOARDSIZE];
int score;
int need_random = 1;
int failed;

void print_board_value(int x){
    if(x == 2) printf("%5d |", x);
    else if(x == 4) printf("\033[0;32m%5d\033[0m |", x);
    else if(x == 8) printf("\033[0;33m%5d\033[0m |", x);
    else if(x == 16) printf("\033[0;91m%5d\033[0m |", x);
    else if(x == 32) printf("\033[0;96m%5d\033[0m |", x);
    else if(x == 64) printf("\033[0;93m%5d\033[0m |", x);
    else if(x == 128) printf("\033[0;94m%5d\033[0m |", x);
    else if(x == 256) printf("\033[0;95m%5d\033[0m |", x);
    else if(x == 512) printf("\033[0;96m%5d\033[0m |", x);
    else if(x == 1024) printf("\033[0;97m%5d\033[0m |", x);
    else if(x == 2048) printf("\033[0;36m%5d\033[0m |", x);
    else printf("\033[0;100m%5d\033[0m |", x);
}

// print the board
void print_board(){
    system("cls");
    printf("Score: \033[0;31m%d\033[0m\n", score);
    if(!failed) printf("\"WASD\" or arrow key to control.");
    else printf("\033[0;31mgame over! do you want to replay?[y/n]\033[0m");
    puts("");puts("");

    // board
    printf("|");
    for(int i=0; i<BOARDSIZE; i++) printf("------|");
    puts("");
    for(int i=0; i<BOARDSIZE; i++){
        printf("|");
        for(int j=0; j<BOARDSIZE; j++){
            if(board[i][j]) print_board_value(board[i][j]);
            else printf("      |");
        }
        puts("");
        printf("|");
        for(int j=0; j<BOARDSIZE; j++) printf("------|");
        puts("");
    }

}

// return -1 means game over
int random_2(){
    int blank_list[BOARDSIZE*BOARDSIZE], len=0;
    for(int i=0; i<BOARDSIZE; i++){
        for(int j=0; j<BOARDSIZE; j++){
            if(board[i][j] == 0) blank_list[len++] = i*BOARDSIZE+j;
        }
    }
    if(len == 0) return -1;
    if(need_random == 0) return 0;
    need_random = 0;
    int place = blank_list[rand()%len];
    board[place/BOARDSIZE][place%BOARDSIZE] = 2;
    return 0;
}

// get operation from keyboard
// up is 1, down is 2, right is 3, left is 4
// yes is 5, no is 6, other is 0
int get_operation(){
    int res = 0;
    int ch = getch();
    // arrow key
    if(ch == 224){
        switch (getch()) {
            case KEY_UP:   // arrow up
                res = 1;
                break;
            case KEY_DOWN:   // arrow down
                res = 2;
                break;
            case KEY_RIGHT:   // arrow right
                res = 3;
                break;
            case KEY_LEFT:   // arrow left
                res = 4;
                break;
        }
    }
    else{
        switch (ch) {
            case 'W':
            case 'w':
                res = 1;
                break;
            case 'S':
            case 's':
                res = 2;
                break;
            case 'D':
            case 'd':
                res = 3;
                break;
            case 'A':
            case 'a':
                res = 4;
                break;
            case 'Y':
            case 'y':
                res = 5;
                break;
            case 'N':
            case 'n':
                res = 6;
                break;
            default:
                break;
        }
    }
    fflush(stdin);
    return res;
}

void update_board(){
    int key = get_operation();
    if(key>=1 && key<=4){
        int updated = 0;
        if(key == 1){   // up
            // merge
            for(int i=0; i<BOARDSIZE; i++) {
                // last is index
                int last = -1;
                for (int j = 0; j < BOARDSIZE; j++) {
                    if (board[j][i] == 0) continue;
                    if (last != -1 && board[last][i] == board[j][i]) {
                        board[last][i] *= 2;
                        score += board[last][i];
                        board[j][i] = 0;
                        last = -1;
                        updated = 1;
                        continue;
                    }
                    last = j;
                }
                // move
                for (int j = 1; j < BOARDSIZE; j++) {
                    if (board[j][i] == 0) continue;
                    int k = j;
                    while (k >= 1 && board[k][i] && board[k - 1][i] == 0) {
                        board[k - 1][i] = board[k][i];
                        board[k][i] = 0;
                        k--;
                        updated = 1;
                    }
                }
            }
        }
        else if(key == 2){  // down
            // merge
            for(int i=0; i<BOARDSIZE; i++){
                // last is index
                int last=-1;
                for(int j=BOARDSIZE-1; j>=0; j--){
                    if(board[j][i] == 0) continue;
                    if(last != -1 && board[last][i] == board[j][i]){
                        board[last][i] *= 2;
                        score += board[last][i];
                        board[j][i] = 0;
                        last = -1;
                        updated = 1;
                        continue;
                    }
                    last = j;
                }
                // move
                for(int j=BOARDSIZE-2; j>=0; j--){
                    if(board[j][i] == 0) continue;
                    int k = j;
                    while(k<=BOARDSIZE-2 && board[k][i] && board[k+1][i]==0) {
                        board[k + 1][i] = board[k][i];
                        board[k][i] = 0;
                        k++;
                        updated = 1;
                    }
                }
            }
        }
        else if(key == 3){ // right
            // merge
            for(int i=0; i<BOARDSIZE; i++){
                // last is index
                int last=-1;
                for(int j=BOARDSIZE-1; j>=0; j--){
                    if(board[i][j] == 0) continue;
                    if(last != -1 && board[i][last] == board[i][j]){
                        board[i][last] *= 2;
                        score += board[i][last];
                        board[i][j] = 0;
                        last = -1;
                        updated = 1;
                        continue;
                    }
                    last = j;
                }
                // move
                for(int j=BOARDSIZE-2; j>=0; j--){
                    if(board[i][j] == 0) continue;
                    int k = j;
                    while(k<=BOARDSIZE-2 && board[i][k] && board[i][k+1]==0) {
                        board[i][k + 1] = board[i][k];
                        board[i][k] = 0;
                        k++;
                        updated = 1;
                    }
                }
            }
        }
        else { // left
            // merge
            for(int i=0; i<BOARDSIZE; i++){
                // last is index
                int last=-1;
                for(int j=0; j<BOARDSIZE; j++){
                    if(board[i][j] == 0) continue;
                    if(last != -1 && board[i][last] == board[i][j]){
                        board[i][last] *= 2;
                        score += board[i][last];
                        board[i][j] = 0;
                        last = -1;
                        updated = 1;
                        continue;
                    }
                    last = j;
                }
                // move
                for(int j=1; j<BOARDSIZE; j++){
                    if(board[i][j] == 0) continue;
                    int k = j;
                    while(k>=1 && board[i][k] && board[i][k-1]==0) {
                        board[i][k - 1] = board[i][k];
                        board[i][k] = 0;
                        k--;
                        updated = 1;
                    }
                }
            }
        }
        if(updated) need_random = 1;
    }
    else if(key>=5){
        if(failed) {
            if (key == 5) {
                score = failed = 0;
                need_random = 1;
                for (int i = 0; i < BOARDSIZE; i++)
                    for (int j = 0; j < BOARDSIZE; j++)
                        board[i][j] = 0;
            }
            else {
                printf("Have a good day.\n");
                system("pause");
                exit(0);
            }
        }
    }
}

int main() {
    srand(time(0));

    random_2();
    print_board();
    while(1){
        update_board();

        if (random_2() == -1){
            failed = 1;
        }

        print_board();
    }
    return 0;
}
