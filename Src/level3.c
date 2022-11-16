#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level3.h"
#include "panels.h"
#include "levelSelect.h"
#include "levelTransition.h"

void level3_init(void)
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


	//for loop to go through all the tiles
	for (int width = 0; width < returnBounds(Tile_Size); width++) {

		tiles[width][3].type = WALL;
		tiles[width][6].type = WALL;
	}


	tiles[9][9].type = START;
	tiles[0][4].type = END;

	vents[0].tile1 = &tiles[9][0];
	vents[0].tile2 = &tiles[0][9];

	vents[1].tile1 = &tiles[0][0];
	vents[1].tile2 = &tiles[3][9];

	vents[2].tile1 = &tiles[9][5];
	vents[2].tile2 = &tiles[3][0];

	vents[3].tile1 = &tiles[9][0];
	vents[3].tile2 = &tiles[6][9];

	vents[4].tile1 = &tiles[9][2];
	vents[4].tile2 = &tiles[0][7];

	vents[5].tile1 = &tiles[6][2];
	vents[5].tile2 = &tiles[3][7];

	vents[6].tile1 = &tiles[6][0];
	vents[6].tile2 = &tiles[0][7];

	vents[7].tile1 = &tiles[6][7];
	vents[7].tile2 = &tiles[9][0];

	vents[8].tile1 = &tiles[0][2];
	vents[8].tile2 = &tiles[9][7];

	vents[9].tile1 = &tiles[3][2];
	vents[9].tile2 = &tiles[9][7];

	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 3;
}

void level3_update(void)
{
	switch (gameState) {
	case PLAY:
		if (tileMoveCounter != 0) {}
		else {
			//clears the screen so things can be redrawn
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
			handlePlayerInput(Tile_Size);
			//all the game update methods that needs to be updated every frame
			renderGame();
			//End FOV logic handled area
			drawSideBarStats("Level 3", player.counter);
			if (player.counter < 6)
			{
				drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "Vents are interconnected in unknown ways, you will need to remember which vents leads to which.");

			}
		}
		break;
	case PAUSED:
		drawFullPanel();
		checkClick(startLevelSelect, startLevel3, resumeGame);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel4, startLevel3, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(0,startLevel3, startLevelSelect);
		break;
	case START_TRANSITION:
		CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
		if (levelStarted)	//when level starts, 
		{	//render enter level transition animation
			renderGame();
			levelStarted = initLevelTransition();	//returns 0 when animation is done

			if (!levelStarted)
			{
				gameState = PLAY;
			}
		}
		break;
	}


}

void level3_exit(void)
{
	freeImage();
}