#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct outputs{
    int size;
    int redPawns;
    int bluePawns;
    bool isCorrect;
    bool isGameOver;
    bool isBoardPossible;
    bool canRedWin1Naive;
    bool canBlueWin1Naive;
    bool canRedWin2Naive;
    bool canBlueWin2Naive;
    bool canRedWin1Perfect;
    bool canBlueWin1Perfect;
    bool canRedWin2Perfect;
    bool canBlueWin2Perfect;

    void initOutputs(){
        size = 0;
        redPawns = 0;
        bluePawns = 0;
        isCorrect = false;
        isGameOver = false;
        isBoardPossible = false;
        canRedWin1Naive = false;
        canBlueWin1Naive = false;
        canRedWin2Naive = false;
        canBlueWin2Naive = false;
        canRedWin1Perfect = false;
        canBlueWin1Perfect = false;
        canRedWin2Perfect = false;
        canBlueWin2Perfect = false;
    }
};


void checkBufferForQueries(char * buffer,outputs &out){
    //printf("%s\n",buffer);
    if(strcmp(buffer,"BOARD_SIZE\0") == 0){
        printf("%d\n",out.size);
    }
    else if(strcmp(buffer,"PAWNS_NUMBER\0") == 0){
        printf("%d\n",out.redPawns + out.bluePawns);
    }
    else if(strcmp(buffer,"IS_BOARD_CORRECT\0") == 0){
        int diff = out.redPawns - out.bluePawns;
        if(diff == 1 || diff == 0)printf("YES\n");
        else printf("NO\n");
    }
    printf("\n");
}

int main(){
    outputs out;
    out.initOutputs();
    char board[10][10] = {""};
    char key = 'p';
    char buffer[1000] = "";
    char fieldPawns[11];
    fieldPawns[10]='\0';
    int i = 0;
    int counter = 0;
    bool parsingBoard = false;
    while(key != EOF){
        key = getchar();
        if(key == '\n'){
            buffer[i] = '\0';
            //printf("%s\n",buffer);
            int fields = 0;
            for(int j = 0;j<=i-2;j++){
                if(buffer[j] == '-' && buffer[j+1] == '-' && buffer[j+2] == '-') {
                    if(parsingBoard == true)parsingBoard=false;
                    else{
                        parsingBoard = true;
                        counter = 0;
                        out.initOutputs();
                    } 
                }
                else if(buffer[j] == '<'){
                    fieldPawns[fields] = buffer[j+2];
                    if(fieldPawns[fields] == 'r')out.redPawns++;
                    else if(fieldPawns[fields] == 'b')out.bluePawns++;
                    fields++;
                }
            }
            if(fields != 0 && parsingBoard == true){
                if(fields == counter){
                    for(int j = fields-1;j>=0;j--){
                        board[counter-j-1][j] = fieldPawns[j];

                    }
                    out.size = counter;
                }
                else if(counter <= (out.size*2)-1){  
                    int temp = counter % out.size;
                    int k = 0;
                    for(int j = out.size-1;j>=out.size-fields;j--){
                        board[j][temp+k] = fieldPawns[k];
                        k++;
                    }
                }
            }
            else if(parsingBoard == false && 'A' <= buffer[0] && buffer[0] <= 'Z'){
                // for(int j = 0;j<out.size;j++){
                //     for(int k = 0;k<out.size;k++){
                //         printf("%c ",board[j][k]);
                //     }
                //     printf("\n");
                // }
                checkBufferForQueries(buffer,out);
            }            
            for(int j = 0;j<11;j++){
                fieldPawns[j]='\0';
            }
            counter++;
            i=0;
        }
        else{
            buffer[i++] = key;
        }
    
        
        
    } 
    //fieldsArr.s[fieldsArr.counter]='\0';
}