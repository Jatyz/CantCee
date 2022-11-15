#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level10.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"

void level12_init(void)
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

			if (width == 3 || width == 7 || width == 9 || width == 13) {
				tiles[width][height].type = WALL;
			}
			if (height == 3 || height == 7 || height == 11) {
				tiles[width][height].type = WALL;
			}

		}
	}

	tiles[3][15].type = FLOOR;
	tiles[13][15].type = FLOOR;
	tiles[7][13].type = FLOOR;
	tiles[7][14].type = FLOOR;
	tiles[7][15].type = FLOOR;
	tiles[9][13].type = FLOOR;
	tiles[9][14].type = FLOOR;
	tiles[9][15].type = FLOOR;
	tiles[14][3].type = FLOOR;
	tiles[15][3].type = FLOOR;
	tiles[14][7].type = FLOOR;
	tiles[15][7].type = FLOOR;
	tiles[14][11].type = FLOOR;
	tiles[15][11].type = FLOOR;
	tiles[8][3].type = FLOOR;
	tiles[8][7].type = FLOOR;
	tiles[8][11].type = FLOOR;



	tiles[15][0].type = START;
	tiles[8][0].type = END;

	tiles[6][4].type = DISGUISE;
	tiles[6][4].Tile_Color = RED;

	tiles[0][5].type = DISGUISE;
	tiles[0][5].Tile_Color = BLUE;

	tiles[12][4].type = DISGUISE;
	tiles[12][4].Tile_Color = GREEN;

	vents[0].tile1 = &tiles[0][12];
	vents[0].tile2 = &tiles[2][10];

	vents[1].tile1 = &tiles[12][12];
	vents[1].tile2 = &tiles[12][10];

	vents[2].tile1 = &tiles[12][12];
	vents[2].tile2 = &tiles[12][2];

	vents[3].tile1 = &tiles[12][2];
	vents[3].tile2 = &tiles[6][10];

	vents[4].tile1 = &tiles[4][12];
	vents[4].tile2 = &tiles[6][10];

	vents[5].tile1 = &tiles[0][8];
	vents[5].tile2 = &tiles[6][6];

	vents[6].tile1 = &tiles[4][8];
	vents[6].tile2 = &tiles[12][6];

	vents[7].tile1 = &tiles[10][8];
	vents[7].tile2 = &tiles[2][6];

	vents[8].tile1 = &tiles[0][4];
	vents[8].tile2 = &tiles[2][2];

	vents[9].tile1 = &tiles[4][4];
	vents[9].tile2 = &tiles[6][2];

	vents[10].tile1 = &tiles[10][4];
	vents[10].tile2 = &tiles[12][2];

	//gates
	gates[0].Switch = &tiles[2][0];
	gates[0].Door = &tiles[8][2];

	gates[1].Switch = &tiles[2][4];
	gates[1].Door = &tiles[8][4];

	gates[2].Switch = &tiles[6][0];
	gates[2].Door = &tiles[8][6];

	gates[3].Switch = &tiles[12][0];
	gates[3].Door = &tiles[8][8];


	enemySet(9, 13, 1, 0, AOE_VIEW, GREEN);
	enemySet(7, 13, 1, 0, AOE_VIEW, GREEN);
	enemySet(0, 1, 0, 5, VERTICAL_HORIZONTAL_LOOK, RED);

	setStartGame(Tile_Size);

	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 12;
	gameFogRange = 2;
	player.shineCount = 0;
}

void level12_update(void)
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
				drawSideBarStats("Level 12", player.counter);

			}
			break;
		case PAUSED:
			drawFullPanel();
			checkClick(startLevelSelect, startLevel12, resumeGame);
			break;
		case WIN:
			drawFullPanel();
			checkClick(startLevel13, startLevel12, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(0, startLevel12, startLevelSelect);
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


void level12_exit(void)
{
	freeImage();
}
