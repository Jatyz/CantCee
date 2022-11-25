//---------------------------------------------------------
// file:	level9.c
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
#include "level9.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "FOV.h"
#include "levelTransition.h"

void level9_init(void)
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

	tiles[1][1].type = WALL;
	tiles[2][1].type = WALL;
	tiles[3][1].type = WALL;
	tiles[4][1].type = WALL;
	tiles[5][1].type = WALL;
	tiles[6][1].type = WALL;
	tiles[7][1].type = WALL;
	tiles[8][1].type = WALL;
	tiles[1][2].type = WALL;
	tiles[1][3].type = WALL;
	tiles[1][4].type = WALL;
	tiles[1][5].type = WALL;
	tiles[1][6].type = WALL;
	tiles[1][7].type = WALL;
	tiles[1][8].type = WALL;
	tiles[2][8].type = WALL;
	tiles[3][8].type = WALL;
	tiles[6][8].type = WALL;
	tiles[7][8].type = WALL;
	tiles[8][8].type = WALL;
	tiles[8][7].type = WALL;
	tiles[8][6].type = WALL;
	tiles[8][5].type = WALL;
	tiles[8][4].type = WALL;
	tiles[8][3].type = WALL;
	tiles[8][2].type = WALL;
	tiles[8][1].type = WALL;
	tiles[3][3].type = WALL;
	tiles[4][3].type = WALL;
	tiles[5][3].type = WALL;
	tiles[6][3].type = WALL;
	tiles[6][4].type = WALL;
	tiles[6][5].type = WALL;
	tiles[6][6].type = WALL;
	tiles[3][4].type = WALL;
	tiles[3][5].type = WALL;
	tiles[3][6].type = WALL;
	tiles[4][6].type = WALL;
	tiles[5][6].type = WALL;

	tiles[5][5].type = END;
	tiles[0][9].type = START;


	gates[0].Door = &tiles[5][3];
	gates[0].Switch = &tiles[9][0];

	tiles[0][0].type = DISGUISE;
	tiles[0][0].Tile_Color = RED;

	//set all enemies
	enemySet(2, 7, 0, 3, VERTICAL_HORIZONTAL_LOOK, RED);

	//set all current level values
	setStartGame(Tile_Size);
	player.setFOV = 1;
	doorLightRange = 2;
	player.currentStage = 9;
	gameFogRange = 1;
}

void level9_update(void)
{
		switch (gameState) {
		case PLAY:
			//if on illum mode and light is still lit
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
				//clear background
				CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
				
				//draw all tiles
				renderGame();

				//handle all player input
				handlePlayerInput(Tile_Size);

				//draw side panels and prompts
				if (player.counter < 10)
				{
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 3 * Tile_Size, 4 * Tile_Size, "It is really dark. I guess you CANT CEE");

				}
				if (player.x == 9 && player.y == 0)
					drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 1 * Tile_Size, 2 * Tile_Size, "Stepping on the switch reveals the door");
				//End FOV logic handled area
				drawSideBarStats("Level 9", player.counter);
			}
			break;
			//draw pause win and lose panels and check for button click input
		case PAUSED:
			drawFullPanel();
			checkClick(startLevelSelect, startLevel9, resumeGame);
			break;
		case WIN:
			drawFullPanel();
			checkClick(startLevel10, startLevel9, startLevelSelect);
			break;
		case LOSE:
			drawFullPanel();
			checkClick(0, startLevel9, startLevelSelect);
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

//free all game resources on exit
void level9_exit(void)
{
	freeGameResources();
}
