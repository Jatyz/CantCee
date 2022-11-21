#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level5.h"
#include "panels.h"
#include "levelSelect.h"
#include "levelTransition.h"

void level5_init(void)
{
	//set window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//set tile size
	Tile_Size = SMALL;

	//reset all arrays and variables and init game resources
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);

	tiles[0][0].type = END;
	tiles[9][9].type = START;

	tiles[2][0].type = WALL;
	tiles[2][1].type = WALL;
	tiles[2][2].type = WALL;
	tiles[2][3].type = WALL;
	tiles[2][4].type = WALL;
	tiles[0][2].type = WALL;
	tiles[0][4].type = WALL;
	tiles[1][4].type = WALL;
	tiles[2][4].type = WALL;
	tiles[3][4].type = WALL;
	tiles[4][4].type = WALL;
	tiles[4][3].type = WALL;
	tiles[4][2].type = WALL;
	tiles[4][0].type = WALL;
	tiles[4][5].type = WALL;
	tiles[4][6].type = WALL;
	tiles[3][6].type = WALL;
	tiles[2][6].type = WALL;
	tiles[0][6].type = WALL;
	tiles[5][6].type = WALL;
	tiles[6][6].type = WALL;
	tiles[6][5].type = WALL;
	tiles[6][4].type = WALL;
	tiles[6][3].type = WALL;
	tiles[6][2].type = WALL;
	tiles[6][1].type = WALL;
	tiles[6][0].type = WALL;	
	tiles[6][7].type = WALL;
	tiles[6][8].type = WALL;
	tiles[5][8].type = WALL;
	tiles[4][8].type = WALL;
	tiles[3][8].type = WALL;
	tiles[2][8].type = WALL;
	tiles[1][8].type = WALL;
	tiles[0][8].type = WALL;
	tiles[7][8].type = WALL;
	tiles[8][8].type = WALL;
	tiles[8][9].type = WALL;
	tiles[8][7].type = WALL;
	tiles[8][6].type = WALL;
	tiles[8][5].type = WALL;
	tiles[8][4].type = WALL;
	tiles[8][3].type = WALL;
	tiles[8][2].type = WALL;
	tiles[8][0].type = WALL;

	vents[0].tile1 = &tiles[9][0];
	vents[0].tile2 = &tiles[0][7];

	vents[1].tile1 = &tiles[3][0];
	vents[1].tile2 = &tiles[7][9];

	vents[2].tile1 = &tiles[7][7];
	vents[2].tile2 = &tiles[5][0];

	vents[3].tile1 = &tiles[0][3];
	vents[3].tile2 = &tiles[3][5];


	gates[0].Door = &tiles[1][2];
	gates[0].Switch = &tiles[0][9];
	gates[1].Door = &tiles[8][1];
	gates[1].Switch = &tiles[5][7];
	gates[2].Door = &tiles[1][6];
	gates[2].Switch = &tiles[5][5];
	gates[3].Door = &tiles[4][1];
	gates[3].Switch = &tiles[1][3];

	//assign current level values
	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 5;
}

void level5_update(void)
{
	switch (gameState) {
	case PLAY:
			//clears the screen so things can be redrawn
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));

			//check for player input
			handlePlayerInput(Tile_Size);

			//draw all game tile
			renderGame();

			//draw side panel
			drawSideBarStats("Level 5", player.counter);
			if (player.counter < 10)
			{
				drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "Just like vents, we do not know which switch goes to which door.");
			}
		break;
	//draw pause win and lose panel and check for button click
	case PAUSED:
		drawFullPanel();
		checkClick(startLevelSelect, startLevel5, resumeGame);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel6, startLevel5, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(0,startLevel5, startLevelSelect);
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
void level5_exit(void)
{
	freeGameResources();
}
