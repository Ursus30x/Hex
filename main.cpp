#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct outputs{
    int fields;
    int pawnsNumber;
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
        *this = {0,0,0,0,0,0,0,0,0,0,0,0};
    }
};


void checkBuffer(char * buffer,outputs &out){
    //printf("%s\n",buffer);
    if(strcmp(buffer,"BOARD_SIZE\0") == 0){
        int board = sqrt(out.fields);
        printf("%d\n",board);
        out.fields = 0;
    }
}


int main(){
    outputs out = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    //out.initOutputs();
    char key = 'p';
    char buffer[1000] = "";
    int i = 0;
    while(key != EOF){
        //printf("%d\n",out.fields);
        key = getchar();
        if(key == '\n'){
            buffer[i] = '\0';
            checkBuffer(buffer,out);
            i = 0;
        }
        else{
            buffer[i++] = key;
        }
        
        if(key == '<')out.fields++;
        
        
    } 
}