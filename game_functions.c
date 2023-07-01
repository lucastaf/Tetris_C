#include "matrix_functions.c"
#include <time.h>
int block_index = 0;
int blocks_indexs[7];

block blocks[7] = {
    {0,0,1,4,{ //Line
    {1},
    {1},
    {1},
    {1}}},

    {0,0,2,3,{ //L Block
    {1,0},
    {1,0},
    {1,1}}},

    {0,0,2,3,{ //J Block
    {0,1},
    {0,1},
    {1,1}}},

    {0,0,3,2,{ //S Block
    {0,1,1},
    {1,1,0}}},

    {0,0,3,2,{ //Z Block
    {1,1,0},
    {0,1,1}}},

    {0,0,3,2,{ //T Block
    {0,1,0},
    {1,1,1}}},
     
    {0,0,2,2,{ //O Block
    {1,1},
    {1,1}}}
};

int CheckPlayerMatrixCollision(block player, matrix screen)
{
    matrix soma = sumBlockMatrix(player, screen);
    int i, j, res = 0;
    for (i = 0; i < soma.height; i++)
    {
        for (j = 0; j < soma.width; j++)
        {
            if (soma.args[i][j] > 1)
            {
                res = 1;
            }
        }
    };

    return res;
};

int CheckCompleteLine(matrix screen){
    int res = 0, countline = 0;
    for (int i = screen.height-1;i>0;i--){
        countline = 0; //contagem de itens na linha
        for (int j = 0;j<screen.width;j++){
            if (screen.args[i][j]){
                countline++; //se o elemento for diferente de 0, conta mais um elemento
            }
        }
        if (countline == screen.width){ 
            res = i; //se o numero de elementos for igual o tamanho da linha (todos elementos sao 1), entao a resposta é a linha
            break;
        }
    }
    return res;
};

matrix MoveElementsDown(int line, matrix screen) {
    for (;line>0;line--){
        for (int i=0;i<screen.width;i++){
            screen.args[line][i] = screen.args[line-1][i]; 
        }
    }
    return screen;
};

block PlayerReset(){
    block NewPlayer = blocks[blocks_indexs[block_index]];
    block_index++;
    if (block_index >= 7) {
        GenerateNewBlocks();
        }
    return NewPlayer;
};

matrix GameReset(matrix screen){
    int i,j;
    
    for (i=0;i<screen.height;i++){
        for (j=0;j<screen.width;j++){
            screen.args[i][j] = 0;
        }  
    }
    return screen;
}

block FindRotationSolution(block player, matrix screen){
    int conclusion = 0;
    int i,j;

	for (i = 0;i<player.height;i++){ //Verifica se da pra joga o player pra cima
	    if (CheckPlayerMatrixCollision(player,screen)){	
		    player.yoffset--;	
	    } else {
		    conclusion = 1;
			break;
		}
	}

    if (!conclusion){ //Verifica se da pra joga o player pra esquerda
        player.yoffset += player.width - 1; //Chegou na conclusão que não é jogar para cima, então corrigi o Y
	    for (j = 0;j<player.width;j++){ 
            if (CheckPlayerMatrixCollision(player,screen)){ 
                player.xoffset--;
           } else{
               conclusion = 2;
               break;
            }
     }
    }   

   if (!conclusion){ //Não da de jogar nem pra cima nem pra esquerda, então desfaz
        player.xoffset += player.width; //Ja que não é jogar para esquerda, corriga o X
        player = AntiClockwise(player);
    }

    return player;

};

void GenerateNewBlocks()
{
 block_index = 0;
 int i, j, CheckRepeat, temp;
 for (i = 0; i < 7; i++) {blocks_indexs[i] = -1;}

 for (i = 0; i < 7; i++ ) {
    do {
        CheckRepeat = 0;  
        temp = rand()%7;
        for (j=0;j<7;j++){
            if (temp == blocks_indexs[j]) {
                CheckRepeat = 1;    
                break;
                }
        } 
     } while (CheckRepeat);
     blocks_indexs[i] = temp;
    } 
};