//---------------------------------------------------------
// file:	enemy.c
// author:	Tengku Danish Ashraf Bin Tengku Azlan
// email:	t.bintengkuazlan@digipen.edu
//
// brief:	handles all enemy functions and 
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

//For AOE Enemy
//(difficulty == 1) Checks 8 grids around AOE Enemy
//(difficulty == 2) Checks 20 grids around AOE Enemy

void enemySet(int width, int height, int difficulty, int range, EnemyType type, Color Color)
{
	enemies[width][height].isActive = 1;
	enemies[width][height].type = type;
	enemies[width][height].range = range;
	enemies[width][height].difficulty = difficulty;
	enemies[width][height].Color = Color;
}

void enemyFOVColorSet(int enemyXPos, int enemyYPos)
{
	if (enemies[enemyXPos][enemyYPos].Color == RED)
	{

		CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 60));
		CP_Settings_Fill(CP_Color_Create(200, 0, 50, 60));
	}

	if (enemies[enemyXPos][enemyYPos].Color == GREEN)
	{
		CP_Settings_Stroke(CP_Color_Create(0, 255, 0, 60));
		CP_Settings_Fill(CP_Color_Create(0, 255, 0, 60));
	}

	if (enemies[enemyXPos][enemyYPos].Color == BLUE)
	{
		CP_Settings_Stroke(CP_Color_Create(0, 0, 255, 60));
		CP_Settings_Fill(CP_Color_Create(0, 0, 255, 60));
	}
}

CP_Color enemyColorSet(int enemyXPos, int enemyYPos)
{
	if (enemies[enemyXPos][enemyYPos].Color == RED)
	{
		return Red;
	}

	if (enemies[enemyXPos][enemyYPos].Color == GREEN)
	{
		return Green;
	}

	if (enemies[enemyXPos][enemyYPos].Color == BLUE)
	{
		return Blue;
	}

	return Red;
}

int enemyBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range, int difficulty)
{
	switch (enemies[enemyXPos][enemyYPos].type)
	{
	case VERTICAL_HORIZONTAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
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
					if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
					{
						goto notTrue;
					}
					else if (player.x == enemyXPos && player.y == enemyYPos)
					{
						gameState = LOSE;
					}
					else
					{
						if (player.x == xPos && player.y == yPos)
						{
							return 1;
						}
					}
				notTrue:;
				}
			}
		}
		else if (difficulty == 2)
		{
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					if (xPos < enemyXPos)
					{
						if (yPos < enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos - 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{

									goto notTruee;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos + 1].type == WALL || (tiles[xPos + 1][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
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
						if (yPos == enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && enemyYPos == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
						if (yPos > enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos + 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								if (tiles[xPos + 1][yPos - 1].type == WALL || (tiles[xPos + 1][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
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
						if (yPos < enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else
							{
								if (player.x == xPos && player.y == yPos)
								{
									return 1;
								}
							}
						}
						else if (yPos == enemyYPos)
						{
							if (player.x == xPos && player.y == yPos)
							{
								gameState = LOSE;
							}
						}
						else if (yPos > enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
							{
								goto notTruee;
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
						if (yPos < enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos - 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos + 1].type == WALL || (tiles[xPos - 1][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
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
						else if (yPos == enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else
							{
								if (player.x == xPos && player.y == yPos)
								{
									return 1;
								}
							}
						}
						else if (yPos > enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos + 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
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
				notTruee:;
				}
			}
		}
		break;

//DIAGONAL ENEMY DOES NOT WORK. DO NOT USE//
	case DIAGONAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
			if (tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL
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
	}
	return 0;
}

void drawBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range, int tileSize, int difficulty)
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
						goto notTrue;
					}
					else
					{
						enemyFOVColorSet(enemyXPos, enemyYPos);
						CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
						CP_Settings_NoStroke();
					}
				notTrue:;
				}
			}
			break;
		case 2:
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					if (xPos < enemyXPos)
					{
						if (yPos < enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos - 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{

									goto notTruee;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos + 1].type == WALL || (tiles[xPos + 1][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
						if (yPos == enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && enemyYPos == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
						if (yPos > enemyYPos)
						{
							if ((enemyXPos - 1) == xPos && (enemyYPos + 1) == yPos)
							{
								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos + 1][yPos].type == WALL || (tiles[xPos + 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								if (tiles[xPos + 1][yPos - 1].type == WALL || (tiles[xPos + 1][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
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
						if (yPos < enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else
							{
								enemyFOVColorSet(enemyXPos, enemyYPos);
								CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
						else if (yPos > enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
							{
								goto notTruee;
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
						if (yPos < enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos - 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos][yPos + 1].type == WALL || (tiles[xPos][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos + 1].type == WALL || (tiles[xPos - 1][yPos + 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else
								{
									enemyFOVColorSet(enemyXPos, enemyYPos);
									CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
									CP_Settings_NoStroke();
								}
							}

						}
						else if (yPos == enemyYPos)
						{
							if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
							{
								goto notTruee;
							}
							else
							{
								enemyFOVColorSet(enemyXPos, enemyYPos);
								CP_Graphics_DrawCircle((xPos + 0.5f) * tileSize, (yPos + 0.5f) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
						else if (yPos > enemyYPos)
						{
							if ((enemyXPos + 1) == xPos && (enemyYPos + 1) == yPos)
							{

								if (tiles[xPos][yPos].type == WALL || (tiles[xPos][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
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
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos].type == WALL || (tiles[xPos - 1][yPos].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
								}
								else if (tiles[xPos - 1][yPos - 1].type == WALL || (tiles[xPos][yPos - 1].type == CLOSED_DOOR))
								{
									goto notTruee;
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
				notTruee:;
				}
			}
			break;
		}
	case DIAGONAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
			if (tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL)
			{
				return;
			}
			//CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			enemyFOVColorSet(enemyXPos, enemyYPos);
			CP_Graphics_DrawCircle((enemyXPos + (xdir * counter) + 0.5f) * tileSize, (enemyYPos + (ydir * counter) + 0.5f) * tileSize, tileSize);
			CP_Settings_NoStroke();
		}
		break;
	}
}

void drawEnemy(int tileSize)
{
	//getting array bounds
	int Horizontal_Tile = returnBounds(tileSize);
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
				case AOE_VIEW:
					drawBounds(0, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);

					CP_Settings_Stroke(enemyColorSet(width, height));
					CP_Settings_Fill(enemyColorSet(width, height));
					CP_Graphics_DrawCircle((width + 0.5f) * tileSize, (height + 0.5f) * tileSize, tileSize);
					CP_Settings_NoStroke();
					CP_Settings_NoFill();
					break;
				case VERTICAL_HORIZONTAL_LOOK:
					drawBounds(1, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(-1, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(0, 1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(0, -1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					
					CP_Settings_Stroke(enemyColorSet(width, height));
					CP_Settings_Fill(enemyColorSet(width, height));
					CP_Graphics_DrawCircle((width + 0.5f) * tileSize, (height + 0.5f) * tileSize, tileSize);
					CP_Settings_NoStroke();
					CP_Settings_NoFill();
					break;

//DIAGONAL ENEMY DOES NOT WORK. DO NOT USE//
				case DIAGONAL_LOOK:
					drawBounds(1, 1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(1, -1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(-1, 1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(-1, -1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					
					CP_Settings_Stroke(enemyColorSet(width, height));
					CP_Settings_Fill(enemyColorSet(width, height));
					CP_Graphics_DrawCircle((width + 0.5f) * tileSize, (height + 0.5f) * tileSize, tileSize);
					CP_Settings_NoStroke();
					CP_Settings_NoFill();
					break;
				default:
					CP_Settings_NoStroke();
					CP_Settings_NoFill();
					break;
				}
			}
		}
	}

}

void enemyFOV(int tileSize)
{
	int Horizontal_Tile = returnBounds(tileSize);
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
						//checks to the right of the enemy and checks if player has entered enemy's FOV
					if (width - player.x > 0 && player.y == height)
					{
						if (abs(width - player.x) <= enemyBounds(-1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							if (player.Player_Color != enemies[width][height].Color)
							{
								gameState = LOSE;
							}
						}
					}
						//checks to the left of the enemy and checks if player has entered enemy's FOV
					else if (width - player.x < 0 && player.y == height)
					{

						if (abs(width - player.x) <= enemyBounds(1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							if (player.Player_Color != enemies[width][height].Color)
							{
								gameState = LOSE;
							}
						}
					}
						//checks to the bottom of the enemy and checks if player has entered enemy's FOV
					else if (player.x == width && height - player.y > 0)
					{
						if (abs(height - player.y) <= enemyBounds(0, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							if (player.Player_Color != enemies[width][height].Color)
							{
								gameState = LOSE;
							}
						}
					}
						//checks to the top of the enemy and checks if player has entered enemy's FOV
					else if (player.x == width && height - player.y < 0)
					{
						if (abs(height - player.y) <= enemyBounds(0, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							if (player.Player_Color != enemies[width][height].Color)
							{
								gameState = LOSE;
							}
						}
					}
						//checks if player is on top of enemy
					else if (player.x == width && player.y == height)
					{
						gameState = LOSE;
					}

					break;
				case AOE_VIEW:
					//checks if player has entered enemy's FOV
					if (player.x == width && player.y == height)
					{
						gameState = LOSE;
					}
					else if (enemyBounds(0, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty) == 1)
					{
						if (player.Player_Color != enemies[width][height].Color)
						{
							gameState = LOSE;
						}
					}
					break;

//DIAGONAL ENEMY DOES NOT WORK. DO NOT USE//
				case DIAGONAL_LOOK:

					if (abs(width - player.x) <= enemyBounds(1, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty)
						&& abs(height - player.y) <= enemyBounds(1, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					{
						gameState = LOSE;
					}
					if (abs(width - player.x) <= enemyBounds(1, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty)
						&& abs(height - player.y) <= enemyBounds(1, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					{
						gameState = LOSE;
					}
					if (abs(width - player.x) <= enemyBounds(-1, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty)
						&& abs(height - player.y) <= enemyBounds(-1, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					{
						gameState = LOSE;
					}
					if (abs(width - player.x) <= enemyBounds(-1, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty)
						&& abs(height - player.y) <= enemyBounds(-1, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					{
						gameState = LOSE;
					}
					break;
				}
			}
		}
	}
}

//void enemySet(int tileSize)
//{
//	int Horizontal_Tile = returnBounds(tileSize);
//	int Vertical_Tile = Horizontal_Tile;
//	int height, width;
//
//	for (width = 0; width < Vertical_Tile; width++)
//	{
//		for (height = 0; height < Horizontal_Tile; height++)
//		{
//			switch (enemies[width][height].type)
//			{
//			case VERTICAL_HORIZONTAL_LOOK:
//				enemies[width][height].isActive = 1;
//				break;
//			case AOE_VIEW:
//				enemies[width][height].isActive = 1;
//				break;
//			default:
//				enemies[width][height].isActive = 0;
//				break;
//			}
//
//		}
//	}
//}

void enemyReset(int tileSize)
{
	int Horizontal_Tile = returnBounds(tileSize);
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
