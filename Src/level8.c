#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level8.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "levelTransition.h"

void level8_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//change this variable to change the number of tiles on the map X by X
	//Factors of 800
	// use these below
	// 20,25,32,40,50,80,100,160
	//e.g. big room = 20
	// medium room = 50
	// small room = 80
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
	tiles[4][9].Tile_Color = YELLOW;
	tiles[6][7].type = DISGUISE;
	tiles[6][7].Tile_Color = RED;

	vents[0].tile1 = &tiles[6][9];
	vents[0].tile2 = &tiles[9][0];

	gates[0].Door = &tiles[1][3];
	gates[0].Switch = &tiles[0][7];
	gates[1].Door = &tiles[2][6];
	gates[1].Switch = &tiles[5][2];

	enemySet(2, 1, 1, 0, AOE_VIEW, YELLOW);
	enemySet(7, 1, 1, 0, AOE_VIEW, YELLOW);
	enemySet(2, 9, 0, 5, VERTICAL_HORIZONTAL_LOOK, RED);

	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 8;
}

void level8_update(void)
{
	switch (gameState) {
	case PLAY:
		 if (tileMoveCounter != 0) {}
		 else {
			 //clears the screen so things can be redrawn
			 CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
			 handlePlayerInput(Tile_Size);
			 //all the game update methods that needs to be updated every frame
			 renderGame();
			 //End FOV logic handled area
			 if (player.counter < 10)
			 {
				 drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "Enemies cannot see through closed doors, but they can see through opened ones.");

			 }
		 }
		 drawSideBarStats("Level 8", player.counter);
		break;
	case PAUSED:
		drawFullPanel();
		checkClick(startLevelSelect, startLevel8, resumeGame);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel9, startLevel8, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(0, startLevel8, startLevelSelect);
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

void level8_exit(void)
{
	freeImage();
}
