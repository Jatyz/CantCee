#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level15.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"
#include "levelTransition.h"

void level15_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	Tile_Size = MEDIUM;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	assignTile(Tile_Size);

	tiles[4][0].type = WALL;
	tiles[4][1].type = WALL;
	tiles[3][1].type = WALL;
	tiles[2][1].type = WALL;
	tiles[1][1].type = WALL;
	tiles[1][2].type = WALL;
	tiles[1][3].type = WALL;
	tiles[1][4].type = WALL;
	tiles[2][4].type = WALL;
	tiles[3][4].type = WALL;
	tiles[3][3].type = WALL;
	tiles[4][3].type = WALL;
	tiles[5][3].type = WALL;
	tiles[6][3].type = WALL;
	tiles[7][3].type = WALL;
	tiles[7][4].type = WALL;
	tiles[7][5].type = WALL;
	tiles[7][6].type = WALL;
	tiles[7][7].type = WALL;
	tiles[7][8].type = WALL;
	tiles[7][9].type = WALL;
	tiles[7][10].type = WALL;
	tiles[6][10].type = WALL;
	tiles[5][10].type = WALL;
	tiles[4][10].type = WALL;
	tiles[3][10].type = WALL;
	tiles[3][9].type = WALL;
	tiles[3][8].type = WALL;
	tiles[3][7].type = WALL;
	tiles[3][11].type = WALL;
	tiles[5][11].type = WALL;
	tiles[5][12].type = WALL;
	tiles[6][12].type = WALL;
	tiles[7][12].type = WALL;
	tiles[8][12].type = WALL;
	tiles[9][12].type = WALL;
	tiles[9][11].type = WALL;
	tiles[9][10].type = WALL;
	tiles[9][9].type = WALL;
	tiles[10][9].type = WALL;
	tiles[11][9].type = WALL;
	tiles[12][9].type = WALL;
	tiles[8][7].type = WALL;
	tiles[9][7].type = WALL;
	tiles[10][7].type = WALL;
	tiles[11][7].type = WALL;
	tiles[12][7].type = WALL;

	tiles[5][5].type = WALL;
	tiles[5][6].type = WALL;
	tiles[5][7].type = WALL;
	tiles[5][8].type = WALL;

	tiles[1][6].type = WALL;
	tiles[1][7].type = WALL;
	tiles[1][8].type = WALL;
	tiles[1][9].type = WALL;
	tiles[1][10].type = WALL;

	tiles[12][0].type = WALL;
	tiles[12][1].type = WALL;
	tiles[11][1].type = WALL;
	tiles[10][1].type = WALL;
	tiles[9][1].type = WALL;
	tiles[8][1].type = WALL;

	tiles[0][12].type = WALL;
	tiles[0][13].type = WALL;
	tiles[0][14].type = WALL;
	tiles[0][15].type = WALL;
	tiles[1][15].type = WALL;

	tiles[2][13].type = WALL;
	tiles[3][13].type = WALL;
	tiles[3][14].type = WALL;
	tiles[4][14].type = WALL;
	tiles[5][14].type = WALL;
	tiles[6][14].type = WALL;
	tiles[7][14].type = WALL;
	tiles[8][14].type = WALL;
	tiles[9][14].type = WALL;
	tiles[10][14].type = WALL;
	tiles[10][15].type = WALL;
	tiles[11][14].type = WALL;
	tiles[12][14].type = WALL;
	tiles[13][14].type = WALL;
	tiles[14][14].type = WALL;

	tiles[14][12].type = WALL;
	tiles[14][11].type = WALL;
	tiles[14][10].type = WALL;
	tiles[14][9].type = WALL;
	tiles[14][8].type = WALL;

	tiles[14][6].type = WALL;
	tiles[14][5].type = WALL;
	tiles[14][4].type = WALL;
	tiles[14][3].type = WALL;
	tiles[14][2].type = WALL;
	tiles[14][1].type = WALL;
	tiles[14][0].type = WALL;
	tiles[13][3].type = WALL;
	tiles[12][3].type = WALL;
	tiles[12][4].type = WALL;
	tiles[12][5].type = WALL;
	tiles[11][3].type = WALL;
	tiles[10][3].type = WALL;
	tiles[9][3].type = WALL;
	tiles[9][4].type = WALL;
	tiles[9][5].type = WALL;

	tiles[11][11].type = WALL;
	tiles[12][11].type = WALL;
	tiles[11][12].type = WALL;
	tiles[12][12].type = WALL;

	tiles[15][0].type = START;
	tiles[3][0].type = END;

	vents[0].tile1 = &tiles[11][15];
	vents[0].tile2 = &tiles[2][3];

	vents[1].tile1 = &tiles[10][10];
	vents[1].tile2 = &tiles[11][4];

	gates[0].Switch = &tiles[11][0];
	gates[0].Door = &tiles[0][1];

	gates[1].Switch = &tiles[6][9];
	gates[1].Door = &tiles[0][2];

	gates[2].Switch = &tiles[6][11];
	gates[2].Door = &tiles[0][3];

	gates[3].Switch = &tiles[9][15];
	gates[3].Door = &tiles[0][4];


	setStartGame(Tile_Size);

	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 15;
	gameFogRange = 2;
	player.shineCount = 0;
}

void level15_update(void)
{
	//need this for light shine on door
		switch (gameState) {
		case PLAY:
			if (lightCounter > 0 || illumMode) {

				lightCounter -= CP_System_GetDt();
				handlePlayerIllumInput();
				renderGame();
				renderFOVAdvance(returnBounds(Tile_Size), returnBounds(Tile_Size), Tile_Size);
				return;
			}
			else if (tileMoveCounter != 0) {}
			else {
				//clears the screen so things can be redrawn
				CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
				//all the game update methods that needs to be updated every frame
				renderGame();
				handlePlayerInput(Tile_Size);
				//End FOV logic handled area
				drawSideBarStats("Level 15", player.counter);

			}
			break;
		case PAUSED:
			drawFullPanel();
			checkClick(startLevelSelect, startLevel15, resumeGame);
			break;
		case WIN:
			drawFullPanel();
			checkClick(0/*startLevel16*/, startLevel15, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(0, startLevel15, startLevelSelect);
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


void level15_exit(void)
{
	freeImage();
}
