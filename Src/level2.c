//---------------------------------------------------------
// file:	level2.c
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
#include "level2.h"
#include "panels.h"
#include "levelSelect.h"
#include "levelTransition.h"

void level2_init(void)
{
	//set window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	//set tile size
	Tile_Size = SMALL;

	//reset all arrays and variables and init game resources
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);

	//for loop to go through all the tiles
		for (int width = 0; width < returnBounds(Tile_Size); width++) {

				tiles[width][5].type = WALL;
		}


	tiles[9][9].type = START;
	tiles[0][4].type = END;
	vents[0].tile1 = &tiles[9][0];
	vents[0].tile2 = &tiles[0][9];

	//set current level values
	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 2;
}

void level2_update(void)
{
	switch (gameState) {
	case PLAY:
			//clears the screen so things can be redrawn
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));

			//check for player input
			handlePlayerInput(Tile_Size);

			//draw game
			renderGame();

			//draw side panel
			drawSideBarStats("Level 2", player.counter);

			if (player.counter < 10)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 0 * Tile_Size, 7 * Tile_Size, "Using the portal below, get to the other side.");

			}
		break;
	case PAUSED:
		//draw pause panel and check for click
		drawFullPanel();
		checkClick(startLevelSelect, startLevel2, resumeGame);
		break;
	case WIN:
		//draw win panel and check for click
		drawFullPanel();
		checkClick(startLevel3, startLevel2, startLevelSelect);
		break;
	case LOSE:
		//draw lose panel and check for button click
		drawFullPanel();
		checkClick(0,startLevel2, startLevelSelect);
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

//free game resources
void level2_exit(void)
{
	freeGameResources();
}