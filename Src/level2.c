#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level2.h"
#include "panels.h"
#include "levelSelect.h"


void level2_init(void)
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

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	assignTile(Tile_Size);

	int width;


	//for loop to go through all the tiles
		for (width = 0; width < returnBounds(Tile_Size); width++) {

				tiles[width][5].type = WALL;
		}


	tiles[9][9].type = START;
	tiles[0][4].type = END;
	vents[0].tile1 = &tiles[9][0];
	vents[0].tile2 = &tiles[0][9];
	setStartGame(Tile_Size);
	player.setFOV = 0;
	gameState = PLAY;
}

void level2_update(void)
{
	switch (gameState) {
	case PLAY:
		//clears the screen so things can be redrawn
		CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
		handlePlayerInput(Tile_Size);
		//all the game update methods that needs to be updated every frame
		renderGame();
		//End FOV logic handled area
		drawSideBar("Level 1", player.counter);
		if (player.counter < 6)
		{
			drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "Get to the vent tile to get to the other side");

		}

		break;
	case PAUSED:
		drawFullPanel();
		checkClick(resumeGame, startLevel2, startLevelSelect);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel3, startLevel2, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(startGame, startLevelSelect, 0);
		break;
	}


}

void level2_exit(void)
{

}