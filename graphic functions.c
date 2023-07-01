#include <raylib.h>
#include "game_functions.c"

void DrawTextCentered(const char *text, int posX, int posY, int fontSize, Color color) //função que desenha texto centralizado
{
    Vector2 text_size = MeasureTextEx(GetFontDefault(),text,fontSize,fontSize/10);
    float halfx = text_size.x/2;
    float halfy = text_size.y/2;
    DrawText(text,posX-halfx,posY-halfy,fontSize,color);
}

void DrawMatrix(matrix screen,int x,int y,int PixelSize, Color Color){ //Desenha a tela principal
Vector2 pos;

int i=0,j=0;
for (i=0;i<screen.height;i++){
    for(j=0;j<screen.width;j++){
        pos.y = (i * PixelSize) + y;
        pos.x = (j * PixelSize) + x;
        if (screen.args[i][j]){
        DrawRectangle(pos.x,pos.y,PixelSize,PixelSize,Color);
        }
    }
}
};

void DrawBlock(block player, int x, int y,int PixelSize, Color Color){
Vector2 pos;

int i=0,j=0;

for (i=0;i<player.height;i++){
    for(j=0;j<player.width;j++){
        pos.y = (i * PixelSize) + (player.yoffset * PixelSize) + y;
        pos.x = (j * PixelSize) + (player.xoffset * PixelSize) +x;
        if (player.args[i][j]){
        DrawRectangle(pos.x,pos.y,PixelSize,PixelSize,Color);
        }
    }
}

}

void DrawMatrixGrid(matrix screen, int x, int y, int PixelSize, Color Color){
    int initx = x;
    int inity = y;
    int finalx = initx + (PixelSize*screen.width);
    int finaly = inity + (PixelSize*screen.height);
    for (int i = 0; i <= screen.height; i++){
        y = (i*PixelSize) + inity;
        DrawLine(initx,y,finalx,y,Color);
    }
    for (int i = 0; i <= screen.width; i ++){
        x = (i*PixelSize) + initx;
        DrawLine(x,inity,x,finaly,Color);
    }

}
