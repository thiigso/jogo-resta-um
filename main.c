#include <stdio.h>
#include <conio.h>

#define ROWS 7
#define COLUMNS 7

#define RESET 10
#define MOVING 3
#define SELECTED 2
#define FILLED 1
#define EMPTY 0
#define OUT -1
#define OUTBOARD -2
#define ERROR -3
#define MOVINGERROR -4


int CustomAbs(int n){
    if(n <0)
        return n * -1;
    else return n;
}

void InitializeGame(int matrix[ROWS][COLUMNS]){

    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLUMNS; j++){

            matrix[i][j] = FILLED;

            if(i==0 || i==1 || i==5 || i==6){
                if(j==0 || j==1 || j==5 || j==6){
                    matrix[i][j] = OUT;
                }
            }
            else if(i==3 && j==3){
                matrix[i][j] = EMPTY;
                
            }

        }
    }
}




void VerifyEndGame(){

}


void PrintGame(int matrix[ROWS][COLUMNS],int position[],int status){

    int backspace=0;

    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLUMNS; j++){
            if(status == MOVING || status == MOVINGERROR){
                if(i == position[0] && j == position[1]){
                    printf("%5c",554);
                    continue;
                }
            }
            else if(status == EMPTY){
                if(i == position[0] && j == position[1]){
                    printf("   ");
                    printf("\033[1;32;44m %d \033[0m",matrix[i][j]);
                    backspace=1;
                    continue;
                }
            }

            if(backspace==1){
                printf("%4d",matrix[i][j]);
                backspace=0;
            }
            else
                printf("%5d",matrix[i][j]);

            if(i==3 && j == 6){                                                 // Lugar onde eu printo mensagem na tela
                if(status == OUTBOARD)
                    printf("      Jogada invalida, voce esta querendo sair do tabuleiro! ");
                if(status == ERROR || status == MOVINGERROR){
                    printf("status do print ERROR - PrintGame %d",status);
                    printf("      Voce nao pode fazer essa jogada!");
                }
            }
        }
        backspace=0;
        printf("\n\n");
    }

}

int CheckMove(int matrix[ROWS][COLUMNS], int positionSelected[], int position[]){

    int diffrow = (position[0]-positionSelected[0]), diffcol = (position[1]-positionSelected[1]);


    if(matrix[position[0]][position[1]] != 0){
        PrintGame(matrix,position,MOVINGERROR);
        return MOVING;
    }
    else{

        if(position[0] == positionSelected[0]){
            if((CustomAbs(diffcol)) == 2){
                printf("Entrou no CheckMove 2\n");
                matrix[position[0]][position[1]] = 1;
                matrix[positionSelected[0]][positionSelected[1]] = 0;
                if(diffcol>0)
                    matrix[position[0]][position[1]-1] = 0;
                else
                    matrix[position[0]][position[1]+1] = 0;    

                PrintGame(matrix,position,EMPTY);
                return RESET;
            }
        }
        if(position[1] == positionSelected[1]){
            if((CustomAbs(diffrow)) == 2){
                printf("Entrou no CheckMove 2\n");
                matrix[position[0]][position[1]] = 1;
                matrix[positionSelected[0]][positionSelected[1]] = 0;
                if(diffrow>0)                                 //Come a pecinha
                    matrix[position[0]-1][position[1]] = 0;
                else
                    matrix[position[0]+1][position[1]] = 0;
                PrintGame(matrix,position,EMPTY);
                return RESET;
            }

        }

        return RESET;                 //Se eu selecionei e tentei jogar num espaco vazio que nao podia, eu reseto aqui

    }
}

int SelectPiece(int matrix[ROWS][COLUMNS], int position[], int status){

    int key1, key2, positionSelected[2];
    PrintGame(matrix,position,status);

    if(status == MOVING){ //Se eu tiver movendo alguma peça aqui salva a posição original selecionda
        positionSelected[0] = position[0];
        positionSelected[1] = position[1];
        printf("Salvou o positionSelected - SelectPiece if\n");
    }

    do{
        key1 = _getch();

        printf("key1 %d \n",key1);

        if(key1 == 13){
            if(status == MOVING){ 
                printf("entrou 13\n");
                status = CheckMove(matrix, positionSelected, position);
                if(status == RESET)
                    return RESET;  // esse retorno nao salva em lugar nenhum, e so para saber que eu estou resetando
                printf("Status after CheckMove %d - SelectPiece\n",status);
                continue;
            }
            else
                return SELECTED;
        }
        else if(key1 == 224){
            switch (key2 = _getch()){
                case 75:  //Left
                    position[1]--;
                    if(position[1] == -1){
                        position[1]++;
                        return OUTBOARD;
                    }
                    else{
                        PrintGame(matrix,position,status);
                        break;
                    }
                case 72:  //Up
                    position[0]--;
                    if(position[0] ==-1){
                        position[0]++;
                        return OUTBOARD;
                    }
                    else{
                        PrintGame(matrix,position,status);
                        break;
                    }
                case 77:  //Right
                    position[1]++;
                    if(position[1] == 7){
                        position[1]--;
                        return OUTBOARD;
                    }
                    else{
                        PrintGame(matrix,position,status);
                        break;
                    }
                case 80:  //Down
                    position[0]++;
                    if(position[0] == 7){
                        position[0]--;
                        return OUTBOARD;
                    }
                    else{
                        PrintGame(matrix,position,status);
                        break;
                    }
                default:
                    return ERROR;
            }
        
        printf(" posrow %d - poscol %d - status %d\n",position[0], position[1],status);
        }
        else
            printf("entrou else do SelectPiece\n");

    }while(key1 == 224 || key1 == 13);
    
    printf("gone to error SelectPiece - status %d\n",status);
    return ERROR;

}



int main(){
    
    int matrix[ROWS][COLUMNS];
    int position[2] = {3,3}, status;

    InitializeGame(matrix);
    //PrintGame(matrix,position,SelectPiece(matrix,position,EMPTY));
    do{
        printf("printou status matrix\n");
        status = SelectPiece(matrix,position,EMPTY);
        
        if(status == OUTBOARD){
            PrintGame(matrix,position,OUTBOARD);
            status = EMPTY;
        }
        if(status == SELECTED)
            if(matrix[position[0]][position[1]] == FILLED){
                status = MOVING;
                SelectPiece(matrix,position,MOVING);
            }
            

    }while(1);

    printf("\n\nreturn - %d\n",SelectPiece(matrix,position,EMPTY));



    printf("out posrow %d - poscol %d\n",position[0], position[1]);



    return 0;
}