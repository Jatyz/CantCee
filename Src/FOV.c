//#include "cprocessing.h"
//#include "grid.h"
//#include "game.h"
//#include "player.h"
//#include <math.h>
//
////fog grid of same size as base game to draw over the render layers as FOV, is 1 when FOV is blocked, 0 when FOV not blocked
//int fog[HORIZONTAL_COUNT][VERTICAL_COUNT];		
//
//
///*
//TILE_SIZE
//*/
//
////update basic logic for drawing a layer of black tiles in the level, except in a circle around the player
//void setIllumination(int const playerXPos, int const playerYPos)
//{
//	for (int i = 0; i < HORIZONTAL_COUNT; i++)			//for each row
//	{
//		for (int j = 0; j < VERTICAL_COUNT; j++)		//for each column
//		{
//			
//			//if (abs(i - playerXPos) < 4
//			//	&&
//			//	abs(j - playerYPos ) < 4) 
//
//			// if in an circular area of 4 tiles around the player
//			if (
//				sqrt((i - playerXPos) * (i - playerXPos)+(j - playerYPos)* (j - playerYPos))
//				< 4)
//			{
//				fog[i][j] = 0;							//set fog in this tile to none
//			}
//			else 
//			{
//				fog[i][j] = 1;							//set fog in this tile to cover tile
//			}
//		}
//	}
//}
//
////update basic logic for not drawing fog along player's line of sight
//void setPlayerFOV(int const playerXPos, int const playerYPos, int const playerPrevPosX, int const playerPrevPosY)
//{	
////	int drawY,			//is one if fov is not blocked by wall, unused till further prototyping
////		drawX;			//is one if fov is not blocked by wall, unused till further prototyping
//
//	//these will be used until there is a way to track previous action
//	int posOffsetX = (playerXPos - playerPrevPosX),		//find the last player movement, values are 0/1
//		posOffsetY = (playerYPos - playerPrevPosY);		//find last player movement in Y, values are 0/1
//
//	int coneRange = 4; //assumed cone range first, make either global or defined after debug done
//
//
//	// if in an circular area of 4 tiles around the player
//	if (abs(posOffsetX))								//if moved in X axis
//	{
//		switch (posOffsetX > 0)					// if offset > 0, player looks right, else left
//		{
//		case 1:
//
//			for (int i = playerXPos; i < HORIZONTAL_COUNT; i++)			//for each row pass player to right side of screen
//			{	
//				//for columns on top, below and occupied by player 
//				for (int j = playerYPos - 1;
//					(j < playerPrevPosY + 2);
//					j++)			
//				{
//					if(!(j >= VERTICAL_COUNT) && !(j < 0))				//dont set value if out of array(vertical check)
//					{
//					fog[i][j] = 0;										//set fog in this tile to none
//					}
//				}
//			}
//			break;
//		default:
//
//			for (int i = playerXPos; i >=0; i--)						//for each row pass player to the left side of the screen
//			{
//				//for columns on top, below and occupied by player 
//				for (int j = playerYPos - 1;
//					(j < playerPrevPosY + 2);
//					j++)
//				{
//					if (!(j >= VERTICAL_COUNT) && !(j < 0))				//dont set value if out of array(vertical check)
//					{
//						fog[i][j] = 0;									//set fog in this tile to none
//					}
//				}
//			}
//			break;
//		}
//	}
//	else
//	{
//		if(abs(posOffsetY))							//if moved in Y axis
//		{
//			switch (posOffsetY > 0)					// if offset > 0, player looks down
//			{
//			case 1:
//				//for rows surrounding/close to player in horizontal axis
//				for (int i = playerXPos - 1;
//					(i < playerXPos + 2);
//					i++)			
//				{
//					for (int j = playerYPos; j < VERTICAL_COUNT; j++)	//for each columns pass player to bottom of screen 
//					{
//						if (!(i >= HORIZONTAL_COUNT) && !(i < 0))		//dont set value if out of array(horizontal check)
//						{
//							fog[i][j] = 0;								//set fog in this tile to none
//						}
//					}
//				}
//				break;
//			default:
//				//for rows surrounding/close to player in horizontal axis
//				for (int i = playerXPos - 1;
//					(i < playerXPos + 2);
//					i++)			
//				{
//					for (int j = playerYPos; j >= 0; j--)				//for each columns pass player to bottom of screen 
//					{
//						if (!(i >= HORIZONTAL_COUNT)&& !(i < 0))		//dont set value if out of array(horizontal check)
//						{
//							fog[i][j] = 0;								//set fog in this tile to none
//						}
//
//					}
//				}
//				break;
//			}
//		}
//	}
//
//}
//
//
//void renderFOVBasic(void) 
//{
//	for (int i = 0; i < HORIZONTAL_COUNT; i++)			//for each row
//	{
//		for (int j = 0; j < VERTICAL_COUNT; j++)		//for each column
//		{
//			switch (fog[i][j]) {
//				case 1:
//					CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
//					CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//					//draw the tile
//					CP_Graphics_DrawRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
//					break;
//				default:
//					break;
//			}
//		}
//	}
//}
//
