#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "player.h"
#include <math.h>

//fog grid of same size as base game to draw over the render layers as FOV, is 1 when FOV is blocked, 0 when FOV not blocked
int fog[HORIZONTAL_COUNT][VERTICAL_COUNT];		


/*
TILE_SIZE
*/

//update basic logic for drawing a layer of black tiles in the level, except in a circle around the player
void setIllumination(int playerXPos, int playerYPos)
{
	for (int i = 0; i < HORIZONTAL_COUNT; i++)			//for each row
	{
		for (int j = 0; j < VERTICAL_COUNT; j++)		//for each column
		{
			
			//if (abs(i - playerXPos) < 4
			//	&&
			//	abs(j - playerYPos ) < 4) 

			// if in an circular area of 4 tiles around the player
			if (
				sqrt((i - playerXPos) * (i - playerXPos)+(j - playerYPos)* (j - playerYPos))
				< 4)
			{
				fog[i][j] = 0;							//set fog in this tile to none
			}
			else 
			{
				fog[i][j] = 1;							//set fog in this tile to cover tile
			}
		}
	}
}

//update basic logic for not drawing fog along player's line of sight
void setPlayerFOV(int playerXPos, int playerYPos, int playerPrevPosX, int playerPrevPosY)
{	
//	int drawY,			//is one if fov is not blocked by wall, unused till further prototyping
//		drawX;			//is one if fov is not blocked by wall, unused till further prototyping

	//these will be used until there is a way to track previous action
	int posOffsetX = playerXPos - playerPrevPosX,		//find the last player movement
		posOffsetY = playerYPos - playerPrevPosY;		//find last player movement in Y


	for (int i = 0; i < HORIZONTAL_COUNT; i++)			//for each row
	{
		for (int j = 0; j < VERTICAL_COUNT; j++)		//for each column
		{

			//if (abs(i - playerXPos) < 4
			//	&&
			//	abs(j - playerYPos ) < 4) 

			// if in an circular area of 4 tiles around the player
			if (
				sqrt((i - playerXPos) * (i - playerXPos) + (j - playerYPos) * (j - playerYPos))
				< 4)
			{
				fog[i][j] = 0;							//set fog in this tile to none
			}
			else
			{
				fog[i][j] = 1;							//set fog in this tile to cover tile
			}
		}
	}
}


void renderFOVBasic(void) 
{
	for (int i = 0; i < HORIZONTAL_COUNT; i++)			//for each row
	{
		for (int j = 0; j < VERTICAL_COUNT; j++)		//for each column
		{
			switch (fog[i][j]) {
				case 1:
					CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
					CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
					//draw the tile
					CP_Graphics_DrawRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
					break;
				default:
					break;
			}
		}
	}
}

