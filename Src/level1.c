#include "player.h"
#include "grid.h"
#include "game.h"
#include "FOV.h"
#include "cprocessing.h"
#include "level1.h"

void level1_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//change this variable to change the number of tiles on the map X by X
	//Factors of 800
	// use these below
	// 20,25,32,40,50,80,100,160
	//e.g. big room = 20
	// medium room = 50
	// small room = 80
	Tile_Size = SMALL;

	setStartGame();
	assignTile(Tile_Size);//assign all tiles

	//hardcode to test drawing make sure only 1 start point
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
	tiles[9][6].type = DISGUISE;
	tiles[9][6].Tile_Color = Red;
	tiles[9][4].type = DISGUISE;
	tiles[9][4].Tile_Color = Blue;
	tiles[0][9].type = DISGUISE;
	tiles[0][9].Tile_Color = Green;


	//top right
	vents[0].tile1 = &tiles[9][0];
	tiles[9][2].type = WALL;
	tiles[8][2].type = WALL;
	tiles[7][2].type = WALL;
	tiles[7][1].type = WALL;
	tiles[7][0].type = WALL;
	//btm left
	vents[0].tile2 = &tiles[0][8];

	setVents();

	tiles[4][5].type = WALL;
	gates[0].Door = &tiles[4][6];
	gates[0].Switch = &tiles[8][1];

	setGates();

	setPlayerStartPoint(Tile_Size);
	player.setFOV = 1;
}

void level1_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
	handlePlayerInput(Tile_Size);
	renderGame();

	//FOV logic handled here
	setPlayerFOVFunnel(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 1, 3);
	setFOVFunnelWallLogic(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 1, 3);
	setIllumination(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), 2);
	//Test code for *AHEM* dynamic *AHEM* style FOV independent of actual grid resolution
	//setIllumination(player.x * 6 + 3, (player.y * 6) + 3, returnBounds(Tile_Size) * 6 + 2, returnBounds(Tile_Size) * 6 + 2, 4 * 6);

	//End FOV logic handled area

	//level select code
	if (CP_Input_KeyDown(KEY_F1)) {
		CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit);
	}
}

void level1_exit(void)
{

}