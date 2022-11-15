#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level11.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"

void level11_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	Tile_Size = MEDIUM;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	assignTile(Tile_Size);

	
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


	enemySet(9, 7, 2, 0, AOE_VIEW, GREEN);

	enemySet(11, 1, 1, 0, AOE_VIEW, RED);

	setStartGame(Tile_Size);

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
				drawSideBarLevel("Level 11", player.counter);

				//write down number of lights and other stats if we are adding more
				drawSideBarStats();
			}
			break;
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
			checkClick(startLevel11, startLevelSelect, 0);
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


void level11_exit(void)
{

}
