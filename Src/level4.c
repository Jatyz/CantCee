#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level4.h"
#include "panels.h"
#include "levelSelect.h"
#include "levelTransition.h"

void level4_init(void)
{
	//set window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//set tile size
	Tile_Size = SMALL;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);

	//assign all level tiles
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


	//assign current level values
	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 4;
}

void level4_update(void)
{
	switch (gameState) {
	case PLAY:
			//clears the screen so things can be redrawn
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));

			//check for player input
			handlePlayerInput(Tile_Size);

			//draw all game tile
			renderGame();

			//draw side bar
			drawSideBarStats("Level 4", player.counter);
			if (player.counter < 10)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 6 * Tile_Size, 1 * Tile_Size, "The switch to the door is in this room.");
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "using the vents you can get over and open the door.");

			}
			if (player.counter > 15)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "After touching the switch, the door is opened");

			}
		break;
	case PAUSED:
		//draw pause panela nd check button click
		drawFullPanel();
		checkClick(startLevelSelect, startLevel4, resumeGame);
		break;
	case WIN:
		//draw win panel and check button click
		drawFullPanel();
		checkClick(startLevel5, startLevel4, startLevelSelect);
		break;
	case LOSE:
		//draw lose panel and check button click
		drawFullPanel();
		checkClick(0,startLevel4, startLevelSelect);
		break;
	case START_TRANSITION:
		//clear background for transition
		CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
		if (levelStarted)	//when level starts, 
		{	//render enter level transition animation
			//render game to draw the init scene
			renderGame();
			//start the transition
			levelStarted = initLevelTransition();	//returns 0 when animation is done
			//start the game
			if (!levelStarted)
			{
				gameState = PLAY;
			}
		}
		break;
	}


}

//free game resources on exit
void level4_exit(void)
{
	freeGameResources();
}
