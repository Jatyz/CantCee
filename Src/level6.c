//---------------------------------------------------------
// file:	level6.c
// author:	Jarran Tan Yan Zhi
// email:	jarranyanzhi.tan@digipen.edu
//
// brief:	All the declration of functions that creates the level and runs the level
//			
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level6.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "levelTransition.h"

void level6_init(void)
{
	//set window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//set tile size
	Tile_Size = SMALL;

	//reset all arrays and variables and init game resources
	resetGame(Tile_Size);


	//for loop to go through all the tiles
	for (int height = 0; height < returnBounds(Tile_Size); height++) {

		for (int width = 0; width < returnBounds(Tile_Size); width++) {

			if (width < 3 || width > 6) {
				tiles[width][height].type = WALL;
			}
			else {
				tiles[width][height].type = FLOOR;

			}

		}
	}

	tiles[5][9].type = START;
	tiles[4][0].type = END;

	//set enemies	
	enemySet(5, 6, 1, 0, AOE_VIEW, 0);

	//set current level values
	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 6;
}

void level6_update(void)
{
	switch (gameState) {
	case PLAY:
			//clears the screen so things can be redrawn
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));

			//check for player input
			handlePlayerInput(Tile_Size);

			//draw game tile
			renderGame();

			//draw sode panels
			drawSideBarStats("Level 6", player.counter);
			if (player.counter < 6)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 0 * Tile_Size, 1 * Tile_Size, "Enemy has their own detection system avoid walking into their vision");
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "You will lose when you walk into their vision");

			}
			if (player.counter > 6)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 0 * Tile_Size, 1 * Tile_Size, "Get to the exit tile to proceed");

			}
		break;
		//draw pause win and lose panel and check for button click
	case PAUSED:
		drawFullPanel();
		checkClick(startLevelSelect, startLevel6, resumeGame);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel7, startLevel6, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(0,startLevel6, startLevelSelect);
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

//free game resources on exit
void level6_exit(void)
{
	freeGameResources();
}
