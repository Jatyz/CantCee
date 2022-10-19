#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"

void game_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));


	assignTile();//assign all tiles
	//hardcode to test drawing
	tiles[0][0].type = END;
	tiles[0][4].type = WALL;
	tiles[1][4].type = WALL;
	tiles[2][4].type = WALL;
	tiles[3][4].type = WALL;
	tiles[4][4].type = WALL;
	tiles[5][4].type = WALL;
	tiles[4][7].type = WALL;
	tiles[5][7].type = WALL;
	tiles[6][7].type = WALL;
	tiles[7][7].type = WALL;
	tiles[8][7].type = WALL;
	tiles[9][7].type = WALL;
	tiles[9][9].type = START;
	tiles[9][6].type = RED;
	tiles[9][4].type = BLUE;
	player.Player_Color = CP_Color_Create(0, 255, 255, 255);
	Green = CP_Color_Create(0,255,0,255);
	Red = CP_Color_Create(255, 0, 0, 255);
	Blue = CP_Color_Create(0, 0, 255, 255);
	setPlayerStartPoint();
	player.height = PLAYER_HEIGHT;
	player.width = PLAYER_WIDTH;
	player.counter = 0;
}

void game_update(void)
{
	handlePlayerInput();
}

void game_exit(void)
{

}

void renderGame() {
	drawTile();
	drawPlayer();
	//drawFOV();
}