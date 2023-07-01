#include <stdio.h>

//Bloco com matrix e coordenada com jogador
typedef struct block 
{
    int xoffset;
    int yoffset;
    int width;
    int height;
    int args[4][4];
} block;

//Matriz fixa, serve para tela
typedef struct matrix 
{
    int height;
    int width;
    int args[20][10];
} matrix;

// Imprimir matriz
void print_matrix(matrix x)
{
    for (int i = 0; i < x.height; i++)
    {
        for (int j = 0; j < x.width; j++)
        {
            printf("%d ", x.args[i][j]);
        }
        printf("\n");
    }
    printf("\n \n");
};

// Transposta Matriz
block transpost(block x)
{
    block begin = x;
    int i = 0;
    int j = 0;

    x.height = begin.width;
    x.width = begin.height;
    for (i = 0; i < x.height; i++)
    {
        for (j = 0; j < x.width; j++)
        {
            x.args[i][j] = begin.args[j][i];
        }
    }

    return x;
};

// Inverter elementos da linha
block invert_lines(block x)
{
    block begin = x;
    int i;
    int j;

    for (i = 0; i < x.height; i++)
    {
        for (j = 0; j < x.width; j++)
        {
            x.args[i][j] = begin.args[i][x.width - j - 1];
        }
    }

    return x;
};

// Rotaciona no sentido horario
block clockwise(block x)
{
    x = transpost(x);
    x = invert_lines(x);

    return x;
};

block AntiClockwise(block x){
    x = invert_lines(x);
    x = transpost(x);

    return x;
};

//Soma o bloco dentro da matriz da tela
matrix sumBlockMatrix(block player, matrix screen)
{
    int startX = player.xoffset;
    int startY = player.yoffset;
    int i, j = 0;
    for (i = 0; i < player.height; i++)
    {
        for (j = 0; j < player.width; j++)
        {
            screen.args[i + startY][j + startX] += player.args[i][j];
        }
    }
    return screen;
};