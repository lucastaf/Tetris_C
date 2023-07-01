#include "graphic functions.c"

int main()
{
	srand(time(NULL));
	GenerateNewBlocks();

	block player;
	block playershadow;
	block nextblock = PlayerReset();
	block stockblock = PlayerReset();
	Color background = BLACK;
	player = PlayerReset();
	player.xoffset = 4;

	int CanChange = 1;
	int score = 0;
	int gameover = 0;

	matrix screen = { //Tela do jogo (zerada)
		20,
		10,
		{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		 }};
		 
	SetTargetFPS(35);
	int framedown = 0;
	int frameside = 0;
	Vector2 screenSize = {630,780};
	InitWindow(screenSize.x,screenSize.y, "Tetris");
	
	while(!WindowShouldClose()){

		if (IsKeyPressed(KEY_R)){ //Game Reset
			screen = GameReset(screen);
			player = PlayerReset();
			nextblock = PlayerReset();
			player.xoffset = 4;
			score = 0;
			gameover = 0;

		}

		if (!gameover){
		//Controle de debugs//
			/*
			if (IsKeyPressed(KEY_W))player.yoffset--;
			if (IsKeyPressed(KEY_S))player.yoffset++;
			if (IsKeyPressed(KEY_D))player = PlayerReset();
			*/
		// ---- //

		//Controles do personagem //
		if (IsKeyDown(KEY_LEFT) && player.xoffset>0){ //Define se o Jogador pode ir para a esquerda
			if (frameside >= 3){
			player.xoffset -= 1;
			frameside = 0;
			if (CheckPlayerMatrixCollision(player,screen)){
				player.xoffset += 1;
			}
			}
		}

		if (IsKeyDown(KEY_RIGHT) && player.xoffset<screen.width-player.width){ //Define se o jogador pode ir para a direita
			if (frameside >= 3){
			player.xoffset += 1;
			frameside = 0;
			if (CheckPlayerMatrixCollision(player,screen)){
				player.xoffset -= 1;
			}
			}
		}

		if (IsKeyPressed(KEY_UP)){ // Define se o player pode rotacionar 90 graus
			player = clockwise(player);
			if (player.xoffset > screen.width - player.width) { //Corrige Colisão com a parede
				player.xoffset = screen.width - player.width;
			}
			if (player.yoffset > screen.height - player.height){ //Corrige Colisão com o chão
				player.yoffset = screen.height - player.height;
			}
			if (CheckPlayerMatrixCollision(player,screen)){ //Corrige a colisão com a propria tela
				player = FindRotationSolution(player,screen);
			}
		}

		if (IsKeyDown(KEY_DOWN)){ //Acelera a caida do bloco
			framedown = 10;
		}

		if (IsKeyPressed(KEY_SPACE)){ //Joga o bloco para a ultima posição possível
			while (1){
				player.yoffset ++;
				if (CheckPlayerMatrixCollision(player,screen)){ //Checa a colisão com a matriz
					framedown = 0;
					player.yoffset --;
					break;
				}
				if (player.yoffset >= screen.height - player.height){ //Checa Colisão do player com o chao
					framedown = 0;
					player.yoffset --;
					break;
		}
			}

		}
	
		if (IsKeyPressed(KEY_Z)){ //Guarda o Bloco Atual
			if (CanChange){ 
		 		CanChange = 0;
		 		block temp = player;
		 		player = stockblock;
		 		stockblock = temp;
		 		stockblock.xoffset = 0, stockblock.yoffset = 0;
			}
		}

		// ----- //

		// Verificação de Colisões //
		framedown++;
		frameside++;
		if (framedown>=8){
			player.yoffset++;
		framedown = 0;
		}

		if (CheckPlayerMatrixCollision(player,screen) || player.yoffset > screen.height - player.height){ // Checa Colisao no proximo frame
			//Checa Colisão com a tela OU colisão com o chão
			player.yoffset--;
			screen = sumBlockMatrix(player,screen);
			player = nextblock;
			player.xoffset = 4;
			nextblock = PlayerReset();
			CanChange = 1;
		}

		playershadow = player;
		while (1){ //Gera a sombra do personagem
				playershadow.yoffset ++;
				if (CheckPlayerMatrixCollision(playershadow,screen) || playershadow.yoffset > screen.height - playershadow.height){ //Checa a colisão com a matriz
					playershadow.yoffset --;
					break;
				}
		}

		// ---- //

		//Caculo de pontos / Game over //
		if (CheckCompleteLine(screen)){ //Procura por linhas completas e abaixa a tela
			score += 100;
			screen = MoveElementsDown(CheckCompleteLine(screen),screen);
		}

		if (CheckPlayerMatrixCollision(player,screen)){ //Define GameOver
			gameover = 1;
		}

		// ---- //
		BeginDrawing();

		ClearBackground(background);

		//Screen
		DrawText(TextFormat("Score: %d",score),50,50,20,WHITE);
		DrawMatrix(screen,100,100,30,WHITE);
		DrawMatrixGrid(screen,100,100,30,GRAY);
		DrawBlock(playershadow,100,100,30,BLUE);

		//GUI	
		//Next Block Box
		DrawRectangle(420,100,150,180,GRAY);
		DrawRectangle(422,102,146,176,background);
		DrawTextCentered("NEXT:",495,90,20,WHITE);
		DrawBlock(nextblock,450,130,30,PURPLE);
		//Hold Block Box
		DrawRectangle(420,510,180,180,GRAY);
		DrawRectangle(422,512,176,176,background);
		DrawTextCentered("HOLD:",510,500,20,WHITE);
		DrawBlock(stockblock,450,540,30,ORANGE);
		

		//PLAYER
		DrawBlock(player,100,100,30,GREEN);
		


		EndDrawing();
		} else {
			BeginDrawing();
			ClearBackground(background);
			DrawTextCentered("GAME OVER",screenSize.x/2,screenSize.y/2 - 120,50,WHITE);
			DrawTextCentered(TextFormat("Final Score: %d",score),screenSize.x/2,screenSize.y/2,40,WHITE);
			DrawTextCentered("Press R to Restart",screenSize.x/2,screenSize.y/2 + 80,40,WHITE);

			EndDrawing();
		}

	}

	CloseWindow();
	return 0;
}