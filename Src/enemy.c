//---------------------------------------------------------
// file:	enemy.c
// author:	Tengku Danish Ashraf Bin Tengku Azlan
// email:	t.bintengkuazlan@digipen.edu
//
// brief:	handles all enemy functions for the game. The functions here control all enemy logic.
//          From the enemy's color, the enemy's type, the range of the enemy's FOV, the drawing of the enemy
//          onto the game screen, and the de-loading of the enemy after the level has ended.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include <math.h>

Enemy enemies[MAX_TILES][MAX_TILES];

//catch-all function to make it easier to load all enemy stats and parameters
void enemySet(int width, int height, int difficulty, int range, EnemyType type, Color Color)
{
	enemies[width][height].isActive = 1;//-----------Set to 1 by default to make it possible to set the position
	enemies[width][height].type = type;//------------Sets the type of the enemy. There are 2 types: VERTICAL_HORIZONTAL_LOOK, and AOE_VIEW.
	enemies[width][height].range = range;//----------Used by the VERTICAL_HORIZONTAL_LOOK enemy to set how many grids in the 4 directions it can see
	enemies[width][height].difficulty = difficulty;//Used by AOE_VIEW enemy. It determines if it is a 3x3 or 5x5 FOV grid around your enemy
	enemies[width][height].Color = Color;//----------Sets the color of the enemy. This affects the color-changing mechanic as it will dictate what color the player needs to be to get past the enemy
}

//sets the enemy's FOV color. The reason this is a separate set of colors is because the FOV has a transparency,
//to allow the player to see themselves when they are behind the FOV layer
void enemyFOVColorSet(int enemyXPos, int enemyYPos)	
{
	if (enemies[enemyXPos][enemyYPos].Color == RED)//---------checks to see if enum COLOR of the enemy is RED. It then assigns a translucent red color to the enemy FOV
	{
		CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 60));
		CP_Settings_Fill(CP_Color_Create(200, 0, 50, 60));
	}

	if (enemies[enemyXPos][enemyYPos].Color == GREEN)//-------checks to see if enum COLOR of the enemy is GREEN. It then assigns a translucent yellow color to the enemy FOV
	{
		CP_Settings_Stroke(CP_Color_Create(255, 255, 0, 60));
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 60));
	}

	if (enemies[enemyXPos][enemyYPos].Color == BLUE)//--------checks to see if enum COLOR of the enemy is BLUE. It then assigns a translucent blue color to the enemy FOV
	{
		CP_Settings_Stroke(CP_Color_Create(0, 0, 255, 60));
		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 60));
	}
}

//sets the enemy's color automatically
CP_Color enemyColorSet(int enemyXPos, int enemyYPos)
{
	if (enemies[enemyXPos][enemyYPos].Color == RED)//--------------------checks if the Enemy's color is red. Then, give it the color red
	{
		return Red;
	}

	if (enemies[enemyXPos][enemyYPos].Color == GREEN)//------------------checks if the Enemy's color is green. Then, give it the color green
	{
		return Yellow;
	}

	if (enemies[enemyXPos][enemyYPos].Color == BLUE)//-------------------checks if the Enemy's color is blue. Then, give it the color blue
	{
		return Blue;
	}

	return Red;
}

//handles the player detection logic for each enemy. The checks are run on a set amount of squares around the enemy
int enemyBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range, int difficulty)
{
	switch (enemies[enemyXPos][enemyYPos].type)
	{
	case VERTICAL_HORIZONTAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{   
			//checks if the grid of position [(counter * x)(counter * y)] is a wall or closed door. If true, return amount of grids the enemy has to check for its FOV
			if ((tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL || tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == CLOSED_DOOR)
				&& (enemyXPos + (xdir * counter) >= 0)
				&& (enemyYPos + (ydir * counter) >= 0)
				&& (enemyXPos + (xdir * counter) <= Tile_Size)
				&& (enemyYPos + (ydir * counter) <= Tile_Size))
			{
				return counter;
			}
		}
		return range;
		break;
	case AOE_VIEW:
		if (difficulty == 1)
		{
			for (int xPos = enemyXPos - 1; xPos < (enemyXPos + 2); xPos++)
			{
				for (int yPos = enemyYPos - 1; yPos < (enemyYPos + 2); yPos++)
				{
					//checks to see if this current grid is on a wall or closed door. If true, DO NOT mark it as part of the enemy's FOV
					if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
					{
						continue;
					}
					//checks to see if the player has entered the same grid as the enemy itself
					else if (player.x == enemyXPos && player.y == enemyYPos)
					{
						gameState = LOSE;
					}
					//check assumes that current grid IS NOT a wall or closed door, and therefore will check if player has entered this FOV
					else
					{
						if (player.x == xPos && player.y == yPos)
						{
							return 1;
						}
					}
				}
			}
		}
		else if (difficulty == 2)
		{
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					//This set of if statements checks where the current grid is relative to the enemy. This makes it easier to track the checks each
					//grid must do in order to produce a more realistic FOV in-game
					if (xPos < enemyXPos)
					{
						//checks 3 grids around itself: immediate right, diagonal bottom right, and below 
						if (yPos < enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos - 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos + 1].type == WALL || (tiles[xPos + 1][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}

						}
						//checks the grid to the immediate right
						if (yPos == enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && enemyYPos == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}

						}
						//checks 3 grids around itself: immediate right, diagonal top right, and above
						if (yPos > enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos + 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								if (tiles[xPos + 1][yPos - 1].type == WALL || (tiles[xPos + 1][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}

						}
					}
					else if (xPos == enemyXPos)
					{
						//checks the grid to the bottom of itself
						if (yPos < enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								continue;
							}
							else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
							{
								continue;

							}
							else
							{
								if (player.x == xPos && player.y == yPos)
								{
									return 1;
								}
							}
						}
						//checks if the player is on the enemy. If true, immediate death regardless of color
						else if (yPos == enemyYPos)
						{
							if (player.x == xPos && player.y == yPos)
							{
								gameState = LOSE;
							}
						}
						//checks the grid to the top of itself
						else if (yPos > enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								continue;

							}
							else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
							{
								continue;
							}
							else
							{
								if (player.x == xPos && player.y == yPos)
								{
									return 1;
								}
							}
						}
					}
					else if (xPos > enemyXPos)
					{						
						//checks 3 grids around itself: immediate left, diagonal bottom left, and below 
						if (yPos < enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos - 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}

								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos + 1].type == WALL || (tiles[xPos - 1][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}

						}
						//checks the grid to the immediate right
						else if (yPos == enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								continue;
							}
							else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
							{
								continue;
							}
							else
							{
								if (player.x == xPos && player.y == yPos)
								{
									return 1;
								}
							}
						}
						//checks 3 grids around itself: immediate left, diagonal top left, and above
						else if (yPos > enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos + 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}

								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}
							else
							{
								if ((tiles[xPos][yPos].type == WALL) || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									if (player.x == xPos && player.y == yPos)
									{
										return 1;
									}
								}
							}

						}
					}
				}
			}
		}
		break;
	}
	return 0;
}

//handles the drawing of the enemy FOV
void drawBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range, float tileSize, int difficulty)
{
	switch (enemies[enemyXPos][enemyYPos].type)
	{
	case VERTICAL_HORIZONTAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
			if ((tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL || tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == CLOSED_DOOR))
			{
				return;
			}
			else
			{
				enemyFOVColorSet(enemyXPos, enemyYPos);
				CP_Graphics_DrawCircle((enemyXPos + (xdir * counter) + 0.5f) * tileSize, (enemyYPos + (ydir * counter) + 0.5f) * tileSize, tileSize);
				CP_Settings_NoStroke();
			}
		}
		break;
	case AOE_VIEW:
		switch (enemies[enemyXPos][enemyYPos].difficulty)
		{
		case 1:
			for (int xPos = enemyXPos - 1; xPos < (enemyXPos + 2); xPos++)
			{
				for (int yPos = enemyYPos - 1; yPos < (enemyYPos + 2); yPos++)
				{
					if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
					{
						continue;
					}
					else
					{
						enemyFOVColorSet(enemyXPos, enemyYPos);
						CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
						CP_Settings_NoStroke();
					}
				}
			}
			break;
		case 2:
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					//This set of if statements checks where the current grid is relative to the enemy. This makes it easier to track the checks each
					//grid must do in order to produce a more realistic FOV in-game
					if (xPos < enemyXPos)
					{
						//checks 3 grids around itself: immediate right, diagonal bottom right, and below 
						if (yPos < enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos - 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos + 1].type == WALL || (tiles[xPos + 1][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
						//checks the grid to the immediate right
						if (yPos == enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && enemyYPos == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
						//checks 3 grids around itself: immediate right, diagonal top right, and above
						if (yPos > enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos + 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								if (tiles[xPos + 1][yPos - 1].type == WALL || (tiles[xPos + 1][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
					}
					else if (xPos == enemyXPos)
					{						
						//checks the grid to the bottom of itself
						if (yPos < enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								continue;
							}
							else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
							{
								continue;
							}
							else
							{
								enemyFOVColorSet(enemyXPos, enemyYPos);
								CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
						//checks the grid to the top of itself
						else if (yPos > enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								continue;
							}
							else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
							{
								continue;
							}
							else
							{
								enemyFOVColorSet(enemyXPos, enemyYPos);
								CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
					}
					else if (xPos > enemyXPos)
					{						
						//checks 3 grids around itself: immediate left, diagonal bottom left, and below 
						if (yPos < enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos - 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}

								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}
							else
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos + 1].type == WALL || (tiles[xPos - 1][yPos + 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((float)(xPos + 0.5) * tileSize, (float)(yPos + 0.5) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
						//checks the grid to the immediate right
						else if (yPos == enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								continue;
							}
							else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
							{
								continue;
							}
							else
							{
								enemyFOVColorSet(enemyXPos, enemyYPos);
								CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
						//checks 3 grids around itself: immediate left, diagonal top left, and above
						else if (yPos > enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos + 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}

								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}
							else
							{
								if ((tiles[xPos][yPos].type == WALL) || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else if (tiles[xPos - 1][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									continue;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
					}
				}
			}
			break;
		}
	}
}

//draws all the enemies on the level
void drawEnemy(float tileSize)
{
	//getting array bounds
	int Horizontal_Tile = returnBounds((int)tileSize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;

	for (width = 0; width < Vertical_Tile; width++)
	{
		for (height = 0; height < Horizontal_Tile; height++)
		{
			if (enemies[width][height].isActive == 1)
			{
				switch (enemies[width][height].type)
				{
				case VERTICAL_HORIZONTAL_LOOK:
					//draws the FOV in the 4 directions of this enemy's FOV
					drawBounds(1, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(-1, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(0, 1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(0, -1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);

					//Sets the color of the enemy using the [enemyColorSet] function
					CP_Settings_Stroke(enemyColorSet(width, height));
					CP_Settings_Fill(enemyColorSet(width, height));
					
					//draws the enemy on screen
					CP_Graphics_DrawCircle((width + 0.5f) * tileSize, (height + 0.5f) * tileSize, tileSize);
					CP_Settings_NoStroke();
					CP_Settings_NoFill();
					break;

				case AOE_VIEW:
					//draws the FOV of the enemy according to the difficulty assigned
					drawBounds(0, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);

					//Sets the color of the enemy using the [enemyColorSet] function
					CP_Settings_Stroke(enemyColorSet(width, height));
					CP_Settings_Fill(enemyColorSet(width, height));

					//draws the enemy on screen
					CP_Graphics_DrawCircle((width + 0.5f) * tileSize, (height + 0.5f) * tileSize, tileSize);
					CP_Settings_NoStroke();
					CP_Settings_NoFill();
					break;
				}
			}
		}
	}

}

//handles the general FOV logic
void enemyFOV(float tileSize)
{
	int Horizontal_Tile = returnBounds((int)tileSize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;

	for (height = 0; height < Horizontal_Tile; height++)
	{
		for (width = 0; width < Vertical_Tile; width++)
		{
			if (enemies[width][height].isActive)
			{
				switch (enemies[width][height].type)
				{
				case VERTICAL_HORIZONTAL_LOOK:
					//checks if player is on top of enemy
					if (player.x == width && player.y == height)
					{
						CP_Sound_PlayAdvanced(loseSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
						gameState = LOSE;

					}

					//checks if the player is on the same y position as the enemy
					else if (player.y == height)
					{
						//checks to the right of the enemy and checks if player has entered enemy's FOV
						if (width - player.x > 0)
						{
							if (abs(width - player.x) <= enemyBounds(-1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
							{
								//checks if player has the same color as the enemy. If not, player dies.
								if (player.Player_Color != enemies[width][height].Color)
								{
									CP_Sound_PlayAdvanced(loseSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
									gameState = LOSE;
								}
							}
						}
						//checks to the left of the enemy and checks if player has entered enemy's FOV
						else if (width - player.x < 0)
						{

							if (abs(width - player.x) <= enemyBounds(1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
							{
								//checks if player has the same color as the enemy. If not, player dies.
								if (player.Player_Color != enemies[width][height].Color)
								{
									CP_Sound_PlayAdvanced(loseSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
									gameState = LOSE;
								}
							}
						}
					}

					//checks if the player is on the same x position as the enemy
					else if (player.x == width)
					{
						//checks to the bottom of the enemy and checks if player has entered enemy's FOV
						if (height - player.y > 0)
						{
							if (abs(height - player.y) <= enemyBounds(0, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
							{
								//checks if player has the same color as the enemy. If not, player dies.
								if (player.Player_Color != enemies[width][height].Color)
								{
									CP_Sound_PlayAdvanced(loseSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
									gameState = LOSE;
								}
							}
						}
						//checks to the top of the enemy and checks if player has entered enemy's FOV
						else if (height - player.y < 0)
						{
							if (abs(height - player.y) <= enemyBounds(0, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
							{
								//checks if player has the same color as the enemy. If not, player dies.
								if (player.Player_Color != enemies[width][height].Color)
								{
									CP_Sound_PlayAdvanced(loseSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
									gameState = LOSE;
								}
							}
						}

					}
					break;
				case AOE_VIEW:
					//checks if player is on top of enemy
					if (player.x == width && player.y == height)
					{
						CP_Sound_PlayAdvanced(loseSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
						gameState = LOSE;
					}

					//does it's FOV check to see if player has entered this enemy's FOV
					else if (enemyBounds(0, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty) == 1)
					{
						//checks if player has the same color as the enemy. If not, player dies.
						if (player.Player_Color != enemies[width][height].Color)
						{
							CP_Sound_PlayAdvanced(loseSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
							gameState = LOSE;
						}
					}
					break;
				}
			}
		}
	}
}

//resets the enemeis on level clear
void enemyReset(float tileSize)
{
	int Horizontal_Tile = returnBounds((int)tileSize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;

	for (width = 0; width < Vertical_Tile; width++)
	{
		for (height = 0; height < Horizontal_Tile; height++)
		{
			CP_Settings_NoStroke();
			CP_Settings_NoFill();
			enemies[width][height].isActive = 0;
			enemies[width][height].range = 0;
			enemies[width][height].difficulty = 0;

		}
	}
}
