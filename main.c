#include <stdio.h>
#include <conio.h>

#define ROWS 7
#define COLUMNS 7

#define WIN 100
#define RESET 10
#define MOVING 3
#define SELECTED 2
#define FILLED 1
#define EMPTY 0
#define OUT -1
#define OUTBOARD -2
#define ERROR -3
#define MOVINGERROR -4
#define LOOSE -100

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
                if(j==0 || j==1 || j==5 || j==6)
                    matrix[i][j] = OUT;
            }
            else if(i==3 && j==3){
                matrix[i][j] = EMPTY;
            }
        }
    }
}

int VerifyEndGame(int matrix[ROWS][COLUMNS]){
    int piecesCount=0, possibleMovesInner=0, possibleMovesOuter=0, horizontalCheck=0, verticalCheck=0, completeLine=0;
    for(int i=0; i<ROWS; i++){ 
        for(int j=0; j<COLUMNS; j++){

            if(i==0 || i==1 || i==5 || i==6 ){
                if(matrix[j][i]==1)
                    verticalCheck++;
                if(verticalCheck == 3)
                    completeLine++;
            }
            if(j==0 || j==1 || j==5 || j==6){
                if(matrix[i][j]==1)
                    horizontalCheck++;
                if(horizontalCheck ==3)
                    completeLine++;
            }
            //printf("HorizontalCheck - %d  VerticalCheck - %d  CompleteLine - %d  PossibleInner - %d   i - %d  j - %d\n",horizontalCheck, verticalCheck, completeLine,possibleMovesInner,i,j);

            if(matrix[i][j] == 1){
                piecesCount++;
                if(i==0){
                    if(matrix[i][j-1] == 1 || matrix[i][j+1] == 1 || matrix[i+1][j] == 1){
                        possibleMovesOuter++;
                        continue;
                    }
                    else
                        continue;
                }
                if(i==6){
                    if(matrix[i][j-1] == 1 || matrix[i][j+1] == 1 || matrix[i-1][j] == 1){
                        possibleMovesOuter++;
                        continue;
                    }
                    else
                        continue;
                }
                if(j==0){
                    if(matrix[i-1][j] == 1 || matrix[i+1][j] == 1 || matrix[i][j+1] == 1){
                        possibleMovesOuter++;
                        continue;
                    }
                    else
                        continue;
                }
                if(j==6){
                    if(matrix[i-1][j] == 1 || matrix[i+1][j] == 1 || matrix[i][j-1] == 1){
                        possibleMovesOuter++;
                        //printf("\npassouaqui\n");
                        continue;
                    }
                    else
                        continue;
                }
                if(matrix[i-1][j] == 1 || matrix[i+1][j] == 1 || matrix[i][j-1] == 1 || matrix[i][j+1] == 1){
                    possibleMovesInner++;
                    //printf("\ni %d - j %d\n",i,j);
                }
            }
        }
        horizontalCheck=0;
        verticalCheck=0;
        printf("\n");
    }

    if(piecesCount == 1)
        return WIN;
    else{
        if((possibleMovesOuter+possibleMovesInner) == 0)
            return LOOSE;
        if(possibleMovesInner == 0 && completeLine !=0)
            return LOOSE;
        return RESET;
    }
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
                    //printf("status do print ERROR - PrintGame %d",status);
                    printf("      Voce nao pode fazer essa jogada!");
                }
            }
        }
        backspace=0;
        printf("\n\n");
    }
    printf("\n");

}

int CheckMove(int matrix[ROWS][COLUMNS], int positionSelected[], int position[]){

    int diffRow = (position[0]-positionSelected[0]), diffCol = (position[1]-positionSelected[1]);
    int posRow = position[0], posCol = position[1], posSelRow = positionSelected[0], posSelCol = positionSelected[1];
    //printf("posRow: %d - posCol %d - posSelRow %d - posSelCol %d\n",posRow,posCol,posSelRow,posSelCol);


    if(matrix[posRow][posCol] != 0){
        PrintGame(matrix,position,MOVINGERROR);
        return MOVING;
    }
    else{
        if(posRow == posSelRow){
            if((CustomAbs(diffCol)) == 2){
                //printf("Entrou no CheckMove 1 diffCol %d\n",diffCol);
                if(diffCol>0)
                    if(matrix[posRow][posCol-1] == 1){
                        matrix[posRow][posCol] = 1;
                        matrix[posSelRow][posSelCol] = 0;                  //Come a pecinha
                        matrix[posRow][posCol-1] = 0;
                    }
                    else
                        return RESET;                                      //Reseta se nao passar por cima de nada
                else
                    if(matrix[posRow][posCol+1] == 1){
                        matrix[posRow][posCol+1] = 0;
                        matrix[posSelRow][posSelCol] = 0;
                        matrix[posRow][posCol] = 1;
                    }
                    else
                        return RESET;                                              
            }
        }
        if(posCol == posSelCol){
            if((CustomAbs(diffRow)) == 2){
                //printf("Entrou no CheckMove 2 diffrow %d\n",diffRow);
                if(diffRow>0)
                    if(matrix[posRow-1][posCol] == 1){
                        matrix[posRow][posCol] = 1;
                        matrix[posSelRow][posSelCol] = 0;                                 
                        matrix[posRow-1][posCol] = 0;
                    }
                    else{
                        return RESET;                     
                    }
                else
                    if(matrix[posRow+1][posCol] == 1){
                        matrix[posRow+1][posCol] = 0;
                        matrix[posSelRow][posSelCol] = 0;
                        matrix[posRow][posCol] = 1;
                    }
                    else{
                        return RESET;                        
                    }
            }
        }
        return VerifyEndGame(matrix);    //Verifica se o Jogo terminou e Retorna WIN/LOOSE && Retorna RESET se: [Completou Jogada, Tentou colocar peça num espaço vazio]                 
    }
}

int SelectPiece(int matrix[ROWS][COLUMNS], int position[], int status){

    int key1, key2, positionSelected[2];
    PrintGame(matrix,position,status);

    if(status == MOVING){ //Se eu tiver movendo alguma peça aqui salva a posição original selecionda
        positionSelected[0] = position[0];
        positionSelected[1] = position[1];
        //printf("Salvou o positionSelected - SelectPiece if\n");
    }

    do{
        key1 = _getch();

        //printf("key1 %d \n",key1);

        if(key1 == 13){
            if(status == MOVING){ 
                //printf("entrou 13\n");
                status = CheckMove(matrix, positionSelected, position);
                if(status == RESET)
                    return RESET;  // esse retorno nao salva em lugar nenhum, e so para saber que eu estou resetando
                if(status == WIN)
                    return WIN;
                if(status == LOOSE)
                    return LOOSE;
                //printf("Status after CheckMove %d - SelectPiece\n",status);
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
        
        //printf(" posrow %d - poscol %d - status %d\n",position[0], position[1],status);
        }
        //else
            //printf("entrou else do SelectPiece\n");

    }while(key1 == 224 || key1 == 13);
    
    //printf("gone to error SelectPiece - status %d\n",status);
    return ERROR;

}

int main(){
    
    int matrix[ROWS][COLUMNS];
    int position[2] = {3,3}, status;

    //int matrix[7][7] = {{-1,-1,1,1,0,-1,-1},{-1,-1,0,0,0,-1,-1},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{-1,-1,0,0,0,-1,-1},{-1,-1,1,0,0,-1,-1}};
    //int matrix[7][7] = {{-1,-1,0,0,0,-1,-1},{-1,-1,0,0,0,-1,-1},{0,0,0,0,0,0,0},{0,0,1,1,0,0,0},{0,0,0,0,0,0,0},{-1,-1,0,0,0,-1,-1},{-1,-1,0,0,0,-1,-1}};
    //int matrix[7][7] = {{-1,-1,0,0,0,-1,-1},{-1,-1,0,0,0,-1,-1},{1,0,0,0,0,0,0},{1,0,0,0,0,0,0},{1,0,0,1,1,0,1},{-1,-1,0,0,0,-1,-1},{-1,-1,1,0,0,-1,-1}};
    //int matrix[7][7] = {{-1,-1,0,1,1,-1,-1},{-1,-1,0,0,0,-1,-1},{1,0,0,0,0,0,1},{1,0,0,0,0,0,0},{1,0,1,0,0,0,0},{-1,-1,0,0,1,-1,-1},{-1,-1,0,1,0,-1,-1}};

    do{
        char answer;

        printf("\n\nBem vindo ao jogo de resta um!\n\nDeseja comecar o jogo? (s/n) ");
        scanf("%c",&answer);

        if(answer == 's' || answer =='S'){
            while(getchar() != '\n');

            InitializeGame(matrix);
            position[0]=3; position[1]=3;    //Inicializa o Jogo

            do{
                printf("\n\n");
                //printf("printou status matrix with status: %d\n",status);
                status = SelectPiece(matrix,position,EMPTY);
                
                if(status == OUTBOARD){
                    PrintGame(matrix,position,OUTBOARD);
                    status = EMPTY;
                }
                if(status == SELECTED)
                    if(matrix[position[0]][position[1]] == FILLED){
                        status = MOVING;
                        status = SelectPiece(matrix,position,MOVING);
                        if(status == WIN){
                            PrintGame(matrix,position,WIN);                    
                            printf("\n\n Voce ganhou o jogo!\n");
                            break;
                        }
                        if(status == LOOSE){
                            PrintGame(matrix,position,LOOSE);
                            printf("\n\n Voce perdeu o jogo!\n");
                            break;
                        }
                    } 
            }while(status != LOOSE);
        }
        if(answer =='n' || answer == 'N'){
            printf("\nOk, o jogo nao ira comecar. Ate logo!");
            break;
        }
        if(status == LOOSE){
            do{
                char answerRepeat;
                printf("\nVoce deseja jogar de novo? (s/n) ");
                scanf("%c",&answerRepeat);
                if(answerRepeat == 's' || answerRepeat == 'S'){
                    while(getchar() != '\n');
                    break;
                }
                if(answerRepeat =='n' || answerRepeat == 'N'){
                    printf("\nOk, o jogo nao ira encerrar. Ate logo!");
                    status = ERROR;
                    break;
                }
                else{
                    while(getchar() != '\n');                 //Limpa Buffer
                    printf("\n\nDigite uma tecla valida!\n\n");
                }
            }while(status != ERROR);
        }
        else{
            while(getchar() != '\n');                 //Limpa Buffer
            printf("\n\nDigite uma tecla valida!\n\n");
        }
    }while(status != ERROR);

    return 0;
}