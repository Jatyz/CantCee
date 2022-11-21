#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level13.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"
#include "levelTransition.h"

void level13_init(void)
{
	//set current wwindow size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	
	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//set tile size
	Tile_Size = MEDIUM;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);

	for (int height = 0; height < returnBounds(Tile_Size); height++) {

		for (int width = 0; width < returnBounds(Tile_Size); width++) {

			if (width == 0 || width == 4 || width == 8 || width == 12) {
				tiles[width][height].type = WALL;
			}
			if (height == 0 || height == 4 || height == 8 || height == 12) {
				tiles[width][height].type = WALL;
			}

		}
	}

	tiles[6][4].type = FLOOR;
	tiles[6][8].type = FLOOR;
	tiles[12][14].type = FLOOR;
	tiles[14][12].type = FLOOR;
	tiles[4][10].type = FLOOR;

	tiles[14][14].type = START;
	tiles[2][2].type = END;

	tiles[6][14].type = DISGUISE;
	tiles[6][14].Tile_Color = RED;
	tiles[10][1].type = DISGUISE;
	tiles[10][1].Tile_Color = GREEN;


	gates[0].Switch = &tiles[15][9];
	gates[0].Door = &tiles[10][12];

	gates[1].Switch = &tiles[15][9];
	gates[1].Door = &tiles[8][14];

	gates[2].Switch = &tiles[15][9];
	gates[2].Door = &tiles[14][8];

	gates[3].Switch = &tiles[11][9];
	gates[3].Door = &tiles[14][4];

	gates[4].Switch = &tiles[15][1];
	gates[4].Door = &tiles[12][6];

	gates[5].Switch = &tiles[15][1];
	gates[5].Door = &tiles[12][2];

	gates[6].Switch = &tiles[9][5];
	gates[6].Door = &tiles[8][10];

	gates[7].Switch = &tiles[9][5];
	gates[7].Door = &tiles[10][8];

	gates[8].Switch = &tiles[7][9];
	gates[8].Door = &tiles[4][6];

	gates[9].Switch = &tiles[7][9];
	gates[9].Door = &tiles[2][8];

	gates[10].Switch = &tiles[7][9];
	gates[10].Door = &tiles[2][12];

	gates[11].Switch = &tiles[1][15];
	gates[11].Door = &tiles[4][2];

	gates[12].Switch = &tiles[1][15];
	gates[12].Door = &tiles[2][8];


	enemySet(10, 6, 1, 0, AOE_VIEW, GREEN);
	//set enemy
	enemySet(10, 6, 1, 0, AOE_VIEW, GREEN);

	enemySet(2, 6, 0, 9, VERTICAL_HORIZONTAL_LOOK, RED);

	//set current level values
	setStartGame(Tile_Size);

	//open closed doors
	tiles[14][8].type = OPENED_DOOR;
	tiles[12][2].type = OPENED_DOOR;
	tiles[2][8].type = OPENED_DOOR;

	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 13;
	gameFogRange = 2;
	player.shineCount = 0;
}

void level13_update(void)
{
	//need this for light shine on door
		switch (gameState) {
		case PLAY:
			if (lightCounter > 0 || illumMode) {
				//reduce light counter
				lightCounter -= CP_System_GetDt();
				//handle special input to detect light click
				handlePlayerIllumInput();
				//draw game but do not update fog
				renderGame();
				//draw fog
				renderFOVAdvance(returnBounds(Tile_Size), returnBounds(Tile_Size), Tile_Size);
				if (lightCounter < 0)
				{
					drawSmallPanel(4 * Tile_Size, 3 * Tile_Size, 6 * Tile_Size, 6 * Tile_Size, "Press Space again to deactivate Shine Mode");

				}
				return;
			}
			else {
				//clears the screen so things can be redrawn
				CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
				
				//draw all game tiles
				renderGame();

				//check for player input
				handlePlayerInput(Tile_Size);

				//End FOV logic handled area
				drawSideBarStats("Level 13", player.counter);

			}
			break;
			//draw pause win and lose panels and check for button input
		case PAUSED:
			drawFullPanel();
			checkClick(startLevelSelect, startLevel13, resumeGame);
			break;
		case WIN:
			drawFullPanel();
			checkClick(startLevel14, startLevel13, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(0, startLevel13, startLevelSelect);
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


//free all game resources on exit
void level13_exit(void)
{
	freeGameResources();
}
