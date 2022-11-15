#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level4.h"
#include "panels.h"
#include "levelSelect.h"


void level4_init(void)
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

		tiles[width][5].type = WALL;
	}

	tiles[5][0].type = WALL;
	tiles[5][1].type = WALL;
	tiles[5][2].type = WALL;
	tiles[5][3].type = WALL;
	tiles[5][4].type = WALL;
	tiles[9][9].type = START;
	tiles[0][0].type = END;
	vents[0].tile1 = &tiles[9][0];
	vents[0].tile2 = &tiles[0][9];
	gates[0].Door = &tiles[2][5];
	gates[0].Switch = &tiles[6][4];

	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 4;
}

void level4_update(void)
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
			drawSideBarLevel("Level 4", player.counter);
			if (player.counter < 10)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 6 * Tile_Size, 1 * Tile_Size, "The switch to the door is in this room.");
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "using the vents you can get over and open the door.");

			}
			if (player.counter > 15)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "After touching the switch, the door is opened");

			}
		}
		break;
	case PAUSED:
		drawFullPanel();
		checkClick(startLevelSelect, startLevel4, resumeGame);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel5, startLevel4, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(0,startLevel4, startLevelSelect);
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

void level4_exit(void)
{
	freeImage();
}
