#include "resources.h"
#include "winCheck.h"
#include "isPossible.h"

bool debug = true;

void copyBoard(char src[MAX_SIZE][MAX_SIZE], char dest[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            dest[i][j] = src[i][j];
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




void checkBufferForQueries(int board[MAX_SIZE][MAX_SIZE],char* buffer, outputs& out) {
    if (strncmp(buffer, "BOARD_SIZE", BOARD_LEN) == 0) {
        printf("%d\n\n", out.size);
    } else if (strncmp(buffer, "PAWNS_NUMBER", PAWNS_LEN) == 0) {
        printf("%d\n\n", out.redPawns + out.bluePawns);
        printf("\n");
    } else if (strncmp(buffer, "IS_BOARD_CORRECT", CORRECT_LEN) == 0) {
        if (out.isCorrect)
            printf("YES\n\n");
        else
            printf("NO\n\n");
    } else if (strncmp(buffer, "IS_GAME_OVER", OVER_LEN) == 0) {
        if (out.isCorrect == false)
            printf("NO\n\n");
        else if (out.redWon)
            printf("YES RED\n\n");
        else if (out.blueWon)
            printf("YES BLUE\n\n");
        else
            printf("NO\n\n");
    } else if (strncmp(buffer, "IS_BOARD_POSSIBLE", POSSIBLE_LEN) == 0) {
        checkIfPossible(board, out);
        if (out.isPossible)
            printf("YES\n\n");
        else
            printf("NO\n\n");
    } else if (strncmp(buffer, "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT",
                       RED_NAIVE1_LEN) == 0) {
        static int testNum = 0;  // debug
        if (debug == true) {
            printf("%d\n", testNum);
            testNum++;
        }
        for (int i = 0; i < 4; i++) {
            if (out.naive[i])
                printf("YES\n");
            else
                printf("NO\n");
        }
        printf("\n");
    }
}

void parsingStart(int board[MAX_SIZE][MAX_SIZE], int& counter, outputs& out) {
    memset(board, Empty, BOARD_MEM_SIZE_INT);
    counter = 0;
    out.initOutputs();
}

void parsingEnd(int board[MAX_SIZE][MAX_SIZE], outputs& out) {
    //printBoard(board,out.size);
    int diff = out.redPawns - out.bluePawns;
    if (diff == 1 || diff == 0)
        out.isCorrect = true;
    else
        out.isCorrect = false;

    checkWins(board, out);
    
    // if (out.isCorrect) checkNaive(board, out, 0);
}

void addToPawnBuffer(char buffer[BUFF_SIZE], int fieldPawns[MAX_SIZE],char pawn,
                     outputs& out, int& fields) {
    if (pawn == 'r') {
        fieldPawns[fields] = Red;
        out.redPawns++;
    } else if (pawn == 'b') {
        fieldPawns[fields] = Blue;
        out.bluePawns++;
    }
    fields++;
}

void getLineToBoard(int board[MAX_SIZE][MAX_SIZE], int fieldPawns[MAX_SIZE],
                    outputs& out, int& fields, int& counter) {
    if (fields == counter) {
        for (int j = fields - 1; j >= 0; j--) {
            board[counter - j - 1][j] = fieldPawns[j];
        }
        out.size = counter;
    } else if (counter <= MAX_HEIGHT) {
        int temp = counter % out.size;
        int k = 0;
        for (int j = out.size - 1; j >= out.size - fields; j--) {
            board[j][temp + k] = fieldPawns[k];
            k++;
        }
    }
}

void parsingCheck(int board[MAX_SIZE][MAX_SIZE], int fieldPawns[MAX_SIZE],
                  char buffer[BUFF_SIZE], outputs& out, int& fields, int& i,
                  int &counter, bool& parsingBoard) {
    for (int j = 0; j <= i - 2; j++) {
        if (strncmp(buffer + j - 1, "---", 3) == 0) {
            if (parsingBoard == true) {
                parsingEnd(board, out);
                parsingBoard = false;
            } else {
                parsingStart(board,counter,out);
                parsingBoard = true;
            }
        } else if (buffer[j] == '<') {
            addToPawnBuffer(buffer, fieldPawns, buffer[j+2], out, fields);
        }
    }
}

int main() {
    printf("\n");

    outputs out = {0};
    
    char key = 'p';
    char buffer[BUFF_SIZE] = "";
    int fieldPawns[MAX_SIZE] = {0}, board[MAX_SIZE][MAX_SIZE] = {0};
    int i = 0, counter = 0;
    bool parsingBoard = false;

    while (key != EOF) {
        key = getchar();
        if (key == '\n') {
            buffer[i] = '\0';
            int fields = 0;
            parsingCheck(board,fieldPawns,buffer,out,fields,i,counter,parsingBoard);
            if (fields != 0 && parsingBoard == true) {
                getLineToBoard(board, fieldPawns, out, fields, counter);
            } else if (parsingBoard == false && 'A' <= buffer[0] &&
                       buffer[0] <= 'Z') {
                checkBufferForQueries(board,buffer, out);
            }
            counter++;
            i = 0;
            memset(fieldPawns, Empty, MAX_SIZE*sizeof(int));
            memset(buffer, '0', BUFF_SIZE*sizeof(char));
        } else {
            buffer[i] = key;
            i++;
        }
    }
}