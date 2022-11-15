#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level13.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"

void level13_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	Tile_Size = MEDIUM;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	assignTile(Tile_Size);

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

	setStartGame(Tile_Size);
	tiles[14][8].type = OPENED_DOOR;
	tiles[12][2].type = OPENED_DOOR;
	tiles[2][8].type = OPENED_DOOR;
	enemySet(10, 6, 1, 0, AOE_VIEW, GREEN);

	enemySet(2, 6, 0, 9, VERTICAL_HORIZONTAL_LOOK, RED);


	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 13;
	gameFogRange = 2;
	player.shineCount = 1;
}

void level13_update(void)
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

				drawFog();

				handlePlayerInput(Tile_Size);

				//End FOV logic handled area
				drawSideBarLevel("Level 13", player.counter);

				//write down number of lights and other stats if we are adding more
				drawSideBarStats();
			}
			break;
		case PAUSED:
			drawFullPanel();
			checkClick(startLevelSelect, startLevel13, resumeGame);
			break;
		case WIN:
			drawFullPanel();
			checkClick(0, startLevel13, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(0, startLevel13, startLevelSelect);
			break;
		case START_TRANSITION:
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
			if (levelStarted)	//when level starts, 
			{	//render enter level transition animation
				renderGame();
				drawFog();
				levelStarted = initLevelTransition();	//returns 0 when animation is done

				if (!levelStarted)
				{
					gameState = PLAY;
				}
			}
			break;
		}

	}


void level13_exit(void)
{

}
