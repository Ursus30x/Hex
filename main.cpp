#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct outputs{
    int size;
    int redPawns;
    int bluePawns;
    bool isCorrect;

    void initOutputs(){
        size = 0;
        redPawns = 0;
        bluePawns = 0;
        isCorrect = false;
    }
};

char board[10][10];
bool visited[10][10];
outputs out;

bool checkIfWon(char team,int x,int y){
    visited[x][y]=true;
    if(y==out.size-1 && team == 'r'){
        return true;
    }
    else if(x == out.size-1 && team == 'b'){
        return true;
    }
    else{
        for(int i = -1;i<=1;i++){
            for(int j = -1;j<=1;j++){
                if( 0<=x+i && x+i<out.size
                &&  0<=y+j && y+j<out.size
                &&  i != -1*j
                &&  board  [x+i][y+j] == team
                && !visited[x+i][y+j]){
                    if(checkIfWon(team,x+i,y+j))return true;
                }
            }
        }
    }
    return false;
}

#define BOARD_LEN strlen("BOARD_SIZE")
#define PAWNS_LEN strlen("PAWNS_NUMBER")
#define CORRECT_LEN strlen("IS_BOARD_CORRECT")

void checkBufferForQueries(char * buffer){
    if(strncmp(buffer,"BOARD_SIZE",BOARD_LEN) == 0){
        printf("%d\n",out.size);
    }
    else if(strncmp(buffer,"PAWNS_NUMBER",PAWNS_LEN) == 0){
        printf("%d\n",out.redPawns + out.bluePawns);
    }
    else if(strncmp(buffer,"IS_BOARD_CORRECT",CORRECT_LEN) == 0){
        int diff = out.redPawns - out.bluePawns;
        if(diff == 1 || diff == 0){
            out.isCorrect = true;
            printf("YES\n");
        }
        else{
            out.isCorrect = false;
            printf("NO\n");
        } 
    }
    else if(strcmp(buffer,"IS_GAME_OVER\0") == 0){
        int diff = out.redPawns - out.bluePawns;
        if(diff == 1 || diff == 0){
            out.isCorrect = true;
        }
        else{
            out.isCorrect = false;
        } 
        if(out.isCorrect == false){
            printf("NO\n\n");
            return;
        }
        for(int i = 0;i<out.size-1;i++){
            if(board[i][0] == 'r'){
                if(checkIfWon('r',i,0)){
                    printf("YES RED\n\n");
                    return;
                }
            
            }
            if(board[0][i] == 'b'){
                if(checkIfWon('b',0,i)){
                    printf("YES BLUE\n\n");
                    return;
                }
            }
        }
        printf("NO\n");
    }
    printf("\n");
}

int main(){
    
    out.initOutputs();
    
    char key = 'p';
    char buffer[300] = "";
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
                        for(int n = 0;n<out.size;n++){
                            for(int k = 0;k<out.size;k++){
                                board[n][k] = ' ';
                                visited[n][k] = false;
                            }
                        }
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
                    //printf("%d\n",counter);
                    out.size = counter;
                    //printf("%d\n",out.size);
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
                checkBufferForQueries(buffer);
            }            
            for(int j = 0;j<11;j++){
                fieldPawns[j]='\0';
            }
            counter++;
            i=0;
            memset(buffer,'\0',10000);
        }
        else{
            buffer[i++] = key;
        }
    
        
        
    } 
    //fieldsArr.s[fieldsArr.counter]='\0';
}