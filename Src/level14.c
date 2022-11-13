#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level14.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"

void level14_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	Tile_Size = MEDIUM;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	assignTile(Tile_Size);

	tiles[4][0].type = WALL;
	tiles[4][2].type = WALL;
	tiles[4][3].type = WALL;
	tiles[4][4].type = WALL;
	tiles[4][5].type = WALL;
	tiles[4][6].type = WALL;
	tiles[4][8].type = WALL;
	tiles[4][9].type = WALL;
	tiles[4][10].type = WALL;
	tiles[4][11].type = WALL;
	tiles[4][12].type = WALL;
	tiles[4][13].type = WALL;
	tiles[4][14].type = WALL;
	tiles[10][0].type = WALL;
	tiles[10][2].type = WALL;
	tiles[10][3].type = WALL;
	tiles[10][4].type = WALL;
	tiles[10][5].type = WALL;
	tiles[10][6].type = WALL;
	tiles[10][8].type = WALL;
	tiles[10][9].type = WALL;
	tiles[10][10].type = WALL;
	tiles[10][11].type = WALL;
	tiles[10][12].type = WALL;
	tiles[10][13].type = WALL;
	tiles[10][14].type = WALL;
	tiles[0][12].type = WALL;
	tiles[1][12].type = WALL;
	tiles[3][12].type = WALL;
	tiles[4][12].type = WALL;
	tiles[10][12].type = WALL;
	tiles[11][12].type = WALL;
	tiles[12][12].type = WALL;
	tiles[13][12].type = WALL;
	tiles[14][12].type = WALL;

	tiles[11][9].type = WALL;
	tiles[12][9].type = WALL;
	tiles[14][9].type = WALL;
	tiles[15][9].type = WALL;
	tiles[11][3].type = WALL;
	tiles[12][3].type = WALL;
	tiles[14][3].type = WALL;
	tiles[15][3].type = WALL;
	tiles[0][3].type = WALL;
	tiles[1][3].type = WALL;
	tiles[2][3].type = WALL;
	tiles[3][3].type = WALL;
	tiles[0][6].type = WALL;
	tiles[3][6].type = WALL;
	tiles[4][6].type = WALL;
	tiles[12][5].type = WALL;
	tiles[12][6].type = WALL;
	tiles[12][7].type = WALL;
	tiles[14][5].type = WALL;
	tiles[14][6].type = WALL;
	tiles[14][7].type = WALL;



	tiles[11][13].type = START;
	tiles[1][1].type = END;

	tiles[15][0].type = DISGUISE;
	tiles[15][0].Tile_Color = BLUE;
	tiles[3][5].type = DISGUISE;
	tiles[3][5].Tile_Color = RED;
	tiles[0][7].type = DISGUISE;
	tiles[0][7].Tile_Color = GREEN;

	gates[0].Switch = &tiles[0][13];
	gates[0].Door = &tiles[13][9];

	gates[1].Switch = &tiles[11][10];
	gates[1].Door = &tiles[1][6];

	gates[2].Switch = &tiles[11][4];
	gates[2].Door = &tiles[13][5];

	gates[3].Switch = &tiles[11][4];
	gates[3].Door = &tiles[13][3];

	gates[4].Switch = &tiles[11][4];
	gates[4].Door = &tiles[13][7];

	gates[5].Switch = &tiles[0][5];
	gates[5].Door = &tiles[2][5];

	gates[6].Switch = &tiles[0][5];
	gates[6].Door = &tiles[2][6];


	enemySet(7, 2, 2, 0, AOE_VIEW, RED);
	enemySet(7, 7, 2, 0, AOE_VIEW, GREEN);
	enemySet(7, 12, 2, 0, AOE_VIEW, BLUE);
	enemySet(1, 4, 0, 7, VERTICAL_HORIZONTAL_LOOK, BLUE);
	enemySet(13, 6, 0, 7, VERTICAL_HORIZONTAL_LOOK, RED);

	setStartGame(Tile_Size);

	tiles[1][6].type = OPENED_DOOR;
	tiles[13][5].type = OPENED_DOOR;
	tiles[13][7].type = OPENED_DOOR;
	tiles[13][9].type = OPENED_DOOR;

	player.setFOV = 1;
	doorLightRange = 2;
	gameState = PLAY;
	player.currentStage = 14;
	gameFogRange = 2;
	player.shineCount = 0;
}

void level14_update(void)
{
	//need this for light shine on door
		switch (gameState) {
		case PLAY:
			if (lightCounter > 0 || illumMode) {

				lightCounter -= CP_System_GetDt();
				handlePlayerIllumInput();
				renderGame();
				return;
			}
			else if (tileMoveCounter != 0) {}
			else {
				//clears the screen so things can be redrawn
				CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
				//all the game update methods that needs to be updated every frame
				enemyFOV(Tile_Size);
				if (player.setFOV) {
					clearFogBackground();
					setIlluminationWallLogicOnce(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), gameFogRange+1);

				}

				handlePlayerInput(Tile_Size);

				renderGame();
				//End FOV logic handled area
				drawSideBarLevel("Level 14", player.counter);

				//write down number of lights and other stats if we are adding more
				drawSideBarStats();
			}
			break;
		case PAUSED:
			drawFullPanel();
			checkClick(resumeGame, startLevel14, startLevelSelect);
			break;
		case WIN:
			drawFullPanel();
			checkClick(0/*startLevel15*/, startLevel14, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(startLevel14, startLevelSelect, 0);
			break;
		}

	}


void level14_exit(void)
{

}
