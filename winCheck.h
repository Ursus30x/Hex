#include "resources.h"
#pragma once

bool checkIfWon(int team, int x, int y, int board[MAX_SIZE][MAX_SIZE],
                bool visited[MAX_SIZE][MAX_SIZE], coords winning, int& size) {
    visited[x][y] = true;
    // if(team == 'b')printf("Looking at: %d %d\n",x,y,team);
    if ((y == size - 1 && team == Red) 
    ||  (x == size - 1 && team == Blue)) {
        return true;
    }
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (0 <= x + i && x + i < size 
                && 0 <= y + j && y + j < size 
                && i != -1 * j 
                && board[x + i][y + j] == team 
                && visited[x + i][y + j] != true 
                && !(winning.x == x + i && winning.y == y + j)) {
                if (checkIfWon(team, x + i, y + j, board, visited, winning,
                               size)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkWinFor(int team,int board[MAX_SIZE][MAX_SIZE],const coords &winning, int &size){
    bool visited[MAX_SIZE][MAX_SIZE] = {0};
    int x = 0,y = 0;
    int *ptr;

    //wybieram ktory strone planszy bedzie sprawdzac, y dla niebieskich, x dla czerwonych
    for(int *ptr = (team - 1) ?  &y : &x; *ptr<size; (*ptr)++){
        if(board[x][y] == team && !(winning.x == x && winning.y == y)){
            if(checkIfWon(team,x,y,board,visited,winning,size)){
                return true;
            }
        }
    }
    return false;
}

void checkWins(int board[MAX_SIZE][MAX_SIZE], outputs& out) {
    const coords winning = {-1,-1};
    out.blueWon = checkWinFor(Blue,board, winning, out.size);
    out.redWon = checkWinFor(Red,board, winning, out.size);
}
