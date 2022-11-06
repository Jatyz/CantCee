#include "player.h"
#include "grid.h"
#include "game.h"
#include "FOV.h"
#include "cprocessing.h"
#include "level1.h"
#include "enemy.h"
#include "panels.h"

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
	Tile_Size = MEDIUM;

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

	enemies[3][10].type = AOE_VIEW;
	enemies[3][10].isActive = 2;

	player.setFOV = 1;
	gameState = PLAY;
}

void level1_update(void)
{
	switch (gameState) {
	case PLAY:
		//clears the screen so things can be redrawn
		CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
		handlePlayerInput(Tile_Size);
		//all the game update methods that needs to be updated every frame
		renderGame();
		enemyFOV(Tile_Size);
		//FOV logic handled here
		clearFogBackground();
		//setPlayerFOVFunnel(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 2, 10);
		//setFOVFunnelWallLogic(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 2, 10);
		setIlluminationAdvance(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), 5, 5);

		//Test code for *AHEM* dynamic *AHEM* style FOV independent of actual grid resolution
		//setIllumination(player.x * 6 + 3, (player.y * 6) + 3, returnBounds(Tile_Size) * 6 + 2, returnBounds(Tile_Size) * 6 + 2, 4 * 6);
		// 
		setIlluminationWallLogic(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), 5);
		//End FOV logic handled area
		break;
	case PAUSED:
		drawFullPanel();
		//checkClick(resumeGame, startGame, startLevelSelect);
		break;
	case WIN:
		drawFullPanel();
		//checkClick(startLevel1, startGame, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		//checkClick(startGame, startLevelSelect, 0);
		break;
	}
}

void level1_exit(void)
{

}