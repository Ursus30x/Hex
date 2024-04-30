#include "resources.h"
#include "winCheck.h"

#define EMPTY_OFFSET 1
int getOpponent(int team) { return (team - 1) ? Red : Blue; }

bool generatePositions(int team,int board[MAX_SIZE][MAX_SIZE],outputs &out,int depth, const int desiredDepth){

    for(int i = 0;i<out.size;i++){
        for(int j = 0;j<out.size;j++){
            if(board[i][j] == Empty){
                board[i][j] = team;
                //printBoard(board,out.size);
                bool winningPawn = checkWinFor(team,board,{-1,-1},out.size);
                if(winningPawn == true && depth == desiredDepth){
                    board[i][j]=Empty;
                    return true;
                }
                else if(winningPawn == false && desiredDepth == 2 && depth != 2){

                    if(generatePositions(team,board,out,depth+1,desiredDepth)){
                        board[i][j] = Empty;
                        return true;
                    }
                }
                board[i][j] = Empty;
            }
        }
    }
    return false;
}

bool checkNaive(int team,int board[MAX_SIZE][MAX_SIZE],outputs &out,int depth){
    int pawnsAmount = out.redPawns+out.bluePawns;
    int wolnePola = out.size*out.size - pawnsAmount;
    int turnsNeeded;
    if(team == (pawnsAmount % 2) + 1){
        if(depth == 1)turnsNeeded = 1;
        else if(depth == 2)turnsNeeded = 3;
    }
    else{
        if(depth == 1)turnsNeeded = 2;
        else if(depth == 2)turnsNeeded = 4;
    }

    if(turnsNeeded > wolnePola)return false;

    if(generatePositions(team,board,out,1,depth))return true;
    else return false;
    
    
}