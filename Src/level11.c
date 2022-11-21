#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level11.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"
#include "levelTransition.h"

void level11_init(void)
{
	//set window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//set tile size
	Tile_Size = MEDIUM;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);

	
	tiles[3][0].type = WALL;
	tiles[3][1].type = WALL;
	tiles[3][2].type = WALL;
	tiles[3][3].type = WALL;
	tiles[3][4].type = WALL;
	tiles[3][5].type = WALL;
	tiles[3][6].type = WALL;
	tiles[0][3].type = WALL;
	tiles[1][3].type = WALL;
	tiles[2][3].type = WALL;


	tiles[0][12].type = WALL;
	tiles[2][12].type = WALL;
	tiles[3][12].type = WALL;
	tiles[3][13].type = WALL;
	tiles[3][14].type = WALL;
	tiles[3][15].type = WALL;

	tiles[8][1].type = WALL;
	tiles[8][2].type = WALL;
	tiles[8][3].type = WALL;
	tiles[8][4].type = WALL;
	tiles[7][4].type = WALL;
	tiles[9][4].type = WALL;
	tiles[10][4].type = WALL;
	tiles[11][4].type = WALL;
	tiles[12][4].type = WALL;
	tiles[12][3].type = WALL;
	tiles[13][3].type = WALL;
	tiles[14][3].type = WALL;
	tiles[15][3].type = WALL;
	tiles[12][5].type = WALL;
	tiles[12][6].type = WALL;
	tiles[12][7].type = WALL;
	tiles[12][8].type = WALL;
	tiles[13][7].type = WALL;
	tiles[14][7].type = WALL;
	tiles[15][7].type = WALL;
	tiles[12][8].type = WALL;
	tiles[12][9].type = WALL;
	tiles[12][10].type = WALL;
	tiles[12][11].type = WALL;
	tiles[12][12].type = WALL;
	tiles[14][12].type = WALL;
	tiles[15][12].type = WALL;
	tiles[11][12].type = WALL;
	tiles[10][12].type = WALL;
	tiles[9][12].type = WALL;
	tiles[8][12].type = WALL;
	tiles[7][12].type = WALL;
	tiles[6][12].type = WALL;
	tiles[7][11].type = WALL;
	tiles[7][9].type = WALL;
	tiles[7][8].type = WALL;
	tiles[8][8].type = WALL;
	tiles[9][8].type = WALL;
	tiles[6][8].type = WALL;
	tiles[5][8].type = WALL;
	tiles[4][8].type = WALL;
	tiles[3][8].type = WALL;
	tiles[2][8].type = WALL;
	tiles[0][8].type = WALL;

	tiles[15][13].type = START;
	tiles[0][1].type = END;

	tiles[15][8].type = DISGUISE;
	tiles[15][8].Tile_Color = GREEN;

	tiles[5][14].type = DISGUISE;
	tiles[5][14].Tile_Color = RED;

	vents[0].tile1 = &tiles[2][2];
	vents[0].tile2 = &tiles[15][0];

	vents[1].tile1 = &tiles[15][4];
	vents[1].tile2 = &tiles[0][15];

	gates[0].Switch = &tiles[13][6];
	gates[0].Door = &tiles[7][10];

	gates[1].Switch = &tiles[13][6];
	gates[1].Door = &tiles[13][12];

	gates[2].Switch = &tiles[0][4];
	gates[2].Door = &tiles[1][8];
	
	gates[3].Switch = &tiles[0][4];
	gates[3].Door = &tiles[8][0];

	//set enemies
	enemySet(9, 7, 2, 0, AOE_VIEW, GREEN);

	enemySet(11, 1, 1, 0, AOE_VIEW, RED);

	//set all current level values
	setStartGame(Tile_Size);

	//open some closed doors
	tiles[13][12].type = OPENED_DOOR;	
	tiles[8][0].type = OPENED_DOOR;

	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 11;
	gameFogRange = 2;
	player.shineCount = 0;
}

void level11_update(void)
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
				return;
			}
			else {
				//clears the screen so things can be redrawn
				CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));

				//draw all game tile
				renderGame();

				//handle player input
				handlePlayerInput(Tile_Size);

				//draw tutorial prompts
				if (player.counter < 30) {
					drawSmallPanel(4 * Tile_Size, 3 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "One switch can open/close multiple doors at the same time.");
				}

				//side panels
				drawSideBarStats("Level 11", player.counter);

			}
			break;
			//draw pause menu, win menu and lose menu and check player click
		case PAUSED:
			drawFullPanel();
			checkClick(startLevelSelect, startLevel11, resumeGame);
			break;
		case WIN:
			drawFullPanel();
			checkClick(startLevel12, startLevel11, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(0, startLevel11, startLevelSelect);
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


//free all game resources on esxit
void level11_exit(void)
{
	freeGameResources();
}
