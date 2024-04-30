#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once
#define MAX_SIZE 12  // +1 jako bufor
#define BUFF_SIZE 200
#define MAX_HEIGHT (out.size * 2) - 1
#define IN_BOUNDS (0 <= x + i && x + i < size && 0 <= y + j && y + j < size && i != -1 * j)

#define BOARD_MEM_SIZE_BOOL MAX_SIZE* MAX_SIZE * sizeof(bool)
#define BOARD_MEM_SIZE_CHAR MAX_SIZE* MAX_SIZE * sizeof(char)
#define BOARD_MEM_SIZE_INT MAX_SIZE* MAX_SIZE * sizeof(int)

#define BOARD_LEN strlen("BOARD_SIZE")
#define PAWNS_LEN strlen("PAWNS_NUMBER")
#define CORRECT_LEN strlen("IS_BOARD_CORRECT")
#define OVER_LEN strlen("IS_GAME_OVER")
#define POSSIBLE_LEN strlen("IS_BOARD_POSSIBLE")
#define RED_NAIVE1_LEN strlen("CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
#define RED_NAIVE2_LEN strlen("CAN_RED_WIN_IN_2_MOVE_WITH_NAIVE_OPPONENT")
#define BLUE_NAIVE1_LEN strlen("CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
#define BLUE_NAIVE2_LEN strlen("CAN_BLUE_WIN_IN_2_MOVE_WITH_NAIVE_OPPONENT")

enum TEAMS {
    Empty,
    Red,
    Blue,
};

struct coords {
    int x;
    int y;
};

struct outputs {
    int size;
    int redPawns;
    int bluePawns;
    bool isCorrect;
    bool redWon;
    bool blueWon;
    bool isPossible;
    bool naive[4];

    void initOutputs() {
        size = 0;
        redPawns = 0;
        bluePawns = 0;
        isCorrect = false;
        redWon = false;
        blueWon = false;
        isPossible = false;
        naive[0] = false;
        naive[1] = false;
        naive[2] = false;
        naive[3] = false;
    }
};

void copyBoard(int dest[MAX_SIZE][MAX_SIZE], int src[MAX_SIZE][MAX_SIZE]){
    for(int i = 0;i<MAX_SIZE;i++){
        for(int j = 0;j<MAX_SIZE;j++){
            dest[i][j] = src[i][j];
        }
    }
}

void clearVisited(bool src[MAX_SIZE][MAX_SIZE]){
    for(int i = 0;i<MAX_SIZE;i++){
        for(int j = 0;j<MAX_SIZE;j++){
            src[i][j] = false;
        }
    }
}

void printBoard(int src[12][12], int& size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (src[i][j] == Empty) {
                printf("*");
            } else if (src[i][j] == Red) {
                printf("r");
            } if (src[i][j] == Blue) {
                printf("b");
            } 
        }
        printf("\n");
    }
    printf("\n");
}