#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define MINES 5

char board[N][N];
char show[N][N];


// Utility

int isValid(int r, int c) {
    return (r >= 0 && r < N && c >= 0 && c < N);
}


// count mines around cell
int countAround(int r, int c) {
    int i, j, cnt = 0;

    for (i = r - 1; i <= r + 1; i++) {
        for (j = c - 1; j <= c + 1; j++) {
            if (isValid(i, j)) {
                if (board[i][j] == '*')
                    cnt++;
            }
        }
    }
    return cnt;
}


// Board Setup

void initializeBoards() {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            board[i][j] = '0';
            show[i][j]  = '#';
        }
    }
}


void placeMines() {
    int placed = 0;

    while (placed < MINES) {
        int r = rand() % N;
        int c = rand() % N;

        if (board[r][c] != '*') {
            board[r][c] = '*';
            placed++;
        }
    }
}


void fillNumbers() {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (board[i][j] != '*') {
                board[i][j] = '0' + countAround(i, j);
            }
        }
    }
}


void setupBoard() {
    initializeBoards();
    placeMines();
    fillNumbers();
}



// Printing

void printHeader() {
    int j;
    printf("   ");
    for (j = 0; j < N; j++)
        printf("%d ", j);
    printf("\n");
}

void printShow() {
    int i, j;
    printHeader();

    for (i = 0; i < N; i++) {
        printf("%d: ", i);
        for (j = 0; j < N; j++)
            printf("%c ", show[i][j]);
        printf("\n");
    }
}

void printFinal() {
    int i, j;
    printf("\nFinal Board:\n");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
}



// Gameplay

int reveal(int r, int c) {
    if (show[r][c] == '#') {
        show[r][c] = board[r][c];
        return 1;
    }
    return 0;
}


int handleMove(int r, int c, int *opened) {
    if (!isValid(r, c)) {
        printf("Invalid position!\n");
        return 1;
    }

    if (board[r][c] == '*') {
        printf("BOOM! You hit a mine!\n");
        return 0;
    }

    if (reveal(r, c))
        (*opened)++;
    else
        printf("Already opened!\n");

    return 1;
}


void playGame() {
    setupBoard();

    int safe = N*N - MINES;
    int opened = 0;

    while (1) {
        printShow();

        int r, c;
        printf("Enter row and column: ");

        if (scanf("%d %d", &r, &c) != 2) {
            printf("Invalid input\n");
            break;
        }

        int ok = handleMove(r, c, &opened);

        if (!ok)
            break;

        if (opened == safe) {
            printf("You WIN!\n");
            break;
        }
    }

    printFinal();
}



// Instructions

void instructions() {
    printf("\n=========== INSTRUCTIONS ===========\n");
    printf("1. Board size is 5 x 5\n");
    printf("2. There are 5 mines hidden randomly\n");
    printf("3. Enter row & column to reveal a cell\n");
    printf("4. Number = mines around the cell\n");
    printf("5. Hitting a mine ends the game\n");
    printf("====================================\n\n");
}



// Menu

void menu() {
    while (1) {
        int choice;

        printf("\n============================\n");
        printf("        MINESWEEPER         \n");
        printf("============================\n");
        printf("1. Play Game\n");
        printf("2. Instructions\n");
        printf("3. Exit\n");
        printf("============================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            playGame();
        else if (choice == 2)
            instructions();
        else if (choice == 3) {
            printf("Exiting...\n");
            break;
        }
        else
            printf("Invalid option!\n");
    }
}



// MAIN

int main() {
    srand(time(0));

    menu();

    return 0;
}