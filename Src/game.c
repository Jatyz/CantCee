#include "player.h"
#include "grid.h"
#include "game.h"


void game_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	assignTile();//assign all tiles
	//hardcode to test drawing
	tiles[0][1].type = End;
	tiles[1][1].type = Floor;
	tiles[2][1].type = Floor;
	tiles[2][2].type = Floor;
	tiles[3][2].type = Floor;
	tiles[3][3].type = Floor;
	tiles[3][4].type = Floor;
	tiles[4][4].type = Floor;
	tiles[5][4].type = Floor;
	tiles[5][3].type = Floor;
	tiles[5][2].type = Floor;
	tiles[6][2].type = Floor;
	tiles[7][2].type = Floor;
	tiles[7][3].type = Floor;
	tiles[7][4].type = Floor;
	tiles[7][5].type = Floor;
	tiles[7][6].type = Floor;
	tiles[7][7].type = Start;
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