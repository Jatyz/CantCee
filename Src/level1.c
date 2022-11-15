#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level1.h"
#include "panels.h"
#include "levelSelect.h"
#include "levelTransition.h"
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

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	assignTile(Tile_Size);


	//for loop to go through all the tiles
	for (int height = 0; height < returnBounds(Tile_Size); height++) {

		for (int width = 0; width < returnBounds(Tile_Size); width++) {

			if (width < 3 || width > 6) {
				tiles[width][height].type = WALL;
			}
			else {
				tiles[width][height].type = FLOOR;

			}

		}
	}

	
	tiles[5][9].type = START;
	tiles[4][0].type = END;
	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 1;

}

void level1_update(void)
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
			drawSideBarStats("Level 1", player.counter);
			if (player.y > 5)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "Press WASD to move. Or use mouse to click on a tile to move horizontallly or vertically");

			}
			if (player.counter > 6)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 0 * Tile_Size, 1 * Tile_Size, "Get to the red tile to proceed to next stage");

			}
		}
		break;
	case PAUSED:
		drawFullPanel();
		checkClick(startLevelSelect, startLevel1, resumeGame);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel2, startLevel1, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(0, startLevel1, startLevelSelect);
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

void level1_exit(void)
{
	freeImage();
}