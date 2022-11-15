#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level10.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"

void level10_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	Tile_Size = SMALL;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	assignTile(Tile_Size);

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
	tiles[6][7].Tile_Color = GREEN;

	vents[0].tile1 = &tiles[6][9];
	vents[0].tile2 = &tiles[9][0];

	gates[0].Door = &tiles[1][3];
	gates[0].Switch = &tiles[0][7];
	gates[1].Door = &tiles[2][6];
	gates[1].Switch = &tiles[5][2];

	enemySet(2, 1, 1, 0, AOE_VIEW, RED);
	enemySet(7, 1, 1, 0, AOE_VIEW, RED);
	enemySet(2, 9, 0, 5, VERTICAL_HORIZONTAL_LOOK, GREEN);

	setStartGame(Tile_Size);
	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 10;
	gameFogRange = 2;
	player.shineCount = 1;
}

void level10_update(void)
{
	//need this for light shine on door
		switch (gameState) {
		case PLAY:
			if (lightCounter > 0 || illumMode) {

				lightCounter -= CP_System_GetDt();
				handlePlayerIllumInput();
				renderGame();
				renderFOVAdvance(returnBounds(Tile_Size), returnBounds(Tile_Size), Tile_Size);
				if(player.shineCount > 0 && player.counter < 100)
				drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "click anywhere to shine a light when you have a shine");
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



				//panel
				if (player.counter < 10 && player.shineCount > 0)
				{
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "Press space to activate Illum Mode");

				}
				if (player.counter > 30 && player.counter < 40)
				{
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 1 * Tile_Size, 1 * Tile_Size, "you get a light every 50 steps");

				}

				//End FOV logic handled area
				drawSideBarLevel("Level 10", player.counter);

				//write down number of lights and other stats if we are adding more
				drawSideBarStats();
			}
			break;
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


void level10_exit(void)
{

}
