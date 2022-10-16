#include "player.h"
#include "grid.h"
#include "game.h"


void game_init(void)
{
	CP_System_SetWindowSize(wWidth, wHeight);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	assignTile();//assign all tiles
	//hardcode to test drawing
	tiles[0][1].type = EndPt;
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
	tiles[7][7].type = StartPt;
	setPlayerStartPoint();
	player.height = playerHeight;
	player.width = playerWidth;
}

void game_update(void)
{
	handlePlayerInput();
}

void game_exit(void)
{

}

void render_game() {

	drawTile();
	drawPlayer();
}