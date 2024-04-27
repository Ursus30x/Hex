#include "resources.h"
#include "winCheck.h"

bool basicCheck(outputs &out){
    return  (out.isCorrect == false 
        ||  (out.redPawns > out.bluePawns && out.blueWon) 
        ||  (out.redPawns == out.bluePawns && out.redWon));
}

void checkIfPossible(int board[MAX_SIZE][MAX_SIZE], outputs& out){
    int team = (out.redWon) ? Red : Blue;
    out.isPossible = true;

    if(basicCheck(out))out.isPossible = false;
    else{
        for(int i = 0;i< out.size;i++){
            for(int j = 0;j< out.size;j++){
                const coords winnning = {i,j};
                //printf("lol xd %d %d\n",winnning.x,winnning.y);
                if(checkWinFor(team,board,winnning,out.size) == false){
                    out.isPossible = true;
                    return;
                }
            }
        }
        out.isPossible = false;
    }
}
