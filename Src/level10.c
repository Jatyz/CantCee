#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level10.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"
#include "levelTransition.h"

void level10_init(void)
{
	//set window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//set current tile size
	Tile_Size = SMALL;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);

	tiles[4][0].type = WALL;
	tiles[4][1].type = WALL;
	tiles[4][2].type = WALL;
	tiles[4][3].type = WALL;
	tiles[0][3].type = WALL;
	tiles[1][3].type = WALL;
	tiles[2][3].type = WALL;
	tiles[3][3].type = WALL;
	tiles[5][3].type = WALL;
	tiles[6][3].type = WALL;
	tiles[7][3].type = WALL;
	tiles[8][3].type = WALL;
	tiles[9][3].type = WALL;
	tiles[8][6].type = WALL;
	tiles[7][6].type = WALL;
	tiles[6][6].type = WALL;
	tiles[5][6].type = WALL;
	tiles[3][6].type = WALL;
	tiles[1][6].type = WALL;
	tiles[0][6].type = WALL;
	tiles[3][7].type = WALL;
	tiles[5][7].type = WALL;
	tiles[3][8].type = WALL;
	tiles[5][8].type = WALL;
	tiles[3][9].type = WALL;
	tiles[5][9].type = WALL;


	tiles[9][9].type = START;
	tiles[0][0].type = END;

	tiles[4][9].type = DISGUISE;
	tiles[4][9].Tile_Color = RED;
	tiles[6][7].type = DISGUISE;
	tiles[6][7].Tile_Color = YELLOW;

	vents[0].tile1 = &tiles[6][9];
	vents[0].tile2 = &tiles[9][0];

	gates[0].Door = &tiles[1][3];
	gates[0].Switch = &tiles[0][7];
	gates[1].Door = &tiles[2][6];
	gates[1].Switch = &tiles[5][2];

	//set current enemies
	enemySet(2, 1, 1, 0, AOE_VIEW, RED);
	enemySet(7, 1, 1, 0, AOE_VIEW, RED);
	enemySet(2, 9, 0, 5, VERTICAL_HORIZONTAL_LOOK, YELLOW);

	//set current level values
	setStartGame(Tile_Size);
	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 10;
	gameFogRange = 2;
	player.shineCount = 1;
}

void level10_update(void)
{
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

				if (player.counter < 10 && player.shineCount > 0)
				{
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "Left click on screen to use a shine");

				}

				if (player.counter >10 || player.shineCount == 0 && lightCounter < 0)
				{
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "Press Space again to deactivate Shine Mode");

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

				//draw tutorial prompt panel
				if (player.counter < 10 && player.shineCount > 0)
				{
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "Press space to activate Illum Mode");

				}
				if (player.counter > 30 && player.counter < 40)
				{
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 1 * Tile_Size, 1 * Tile_Size, "you get a light every 50 steps");

				}

				//draw side bar
				drawSideBarStats("Level 10", player.counter);

			}
			break;
			//draw pause win and lose panels and check for panel click
		case PAUSED:
			drawFullPanel();
			checkClick(startLevelSelect, startLevel10, resumeGame);
			break;
		case WIN:
			drawFullPanel();
			checkClick(startLevel11, startLevel10, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(0, startLevel10, startLevelSelect);
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


//free all game reousrces on exit
void level10_exit(void)
{
	freeGameResources();
}
