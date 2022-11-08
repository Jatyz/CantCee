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

int enemyBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range)
{
	for (int counter = 1; counter <= range; counter++)
	{
		if (tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL)
		{
			return counter;
		}
	}
	return range;
}

void drawBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range, int tileSize, int difficulty)
{
	switch (enemies[enemyXPos][enemyYPos].type)
	{
	case FOUR_WAY_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
			if (tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL)
			{
				return NULL;
			}
			CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 40)); //setting stroke color
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 40));   //setting tile color
			CP_Graphics_DrawCircle((enemyXPos + (xdir * counter) + 0.5) * tileSize, (enemyYPos + (ydir * counter) + 0.5) * tileSize, tileSize);
		}
		break;
	case AOE_VIEW:
		if (difficulty == 1)
		{

			CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 40)); //setting stroke color
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 40));   //setting tile color
			for (int xPos = enemyXPos - 1; xPos < (enemyXPos + 2); xPos++)
			{
				for (int yPos = enemyYPos - 1; yPos < (enemyYPos + 2); yPos++)
				{
					if (tiles[xPos][yPos].type != WALL)
					{
						CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
					}
				}
			}
		}

		if (difficulty == 2)
		{
			CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 40)); //setting stroke color
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 40));   //setting tile color
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					if (tiles[xPos][yPos].type != WALL)
					{
						CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
					}
				}
			}
		}
		break;
	}
}

void aoeFOV(int width, int height, int tileSize, int difficulty)
{
	if (difficulty == 1)
	{
		if ((width + 1 == player.x && height == player.y) || (width - 1 == player.x && height == player.y)
			|| (width == player.x && height + 1 == player.y) || (width == player.x && height - 1 == player.y)
			|| (width + 1 == player.x && height + 1 == player.y) || (width - 1 == player.x && height + 1 == player.y)
			|| (width + 1 == player.x && height - 1 == player.y) || (width - 1 == player.x && height - 1 == player.y))
		{
			gameState = LOSE;
		}
	}
	if (difficulty == 2)
	{
		if ((width + 1 == player.x && height == player.y && tiles[width + 1][height].type != WALL)
			|| (width - 1 == player.x && height == player.y && tiles[width - 1][height].type != WALL)
			|| (width == player.x && height + 1 == player.y && tiles[width][height + 1].type != WALL)
			|| (width == player.x && height - 1 == player.y && tiles[width][height - 1].type != WALL)
			|| (width + 1 == player.x && height + 1 == player.y && tiles[width + 1][height + 1].type != WALL)
			|| (width - 1 == player.x && height + 1 == player.y && tiles[width - 1][height + 1].type != WALL)
			|| (width + 1 == player.x && height - 1 == player.y) || (width - 1 == player.x && height - 1 == player.y)
			|| (width + 2 == player.x && height == player.y) || (width - 2 == player.x && height == player.y)
			|| (width == player.x && height + 2 == player.y) || (width == player.x && height - 2 == player.y)
			|| (width + 2 == player.x && height + 1 == player.y) || (width - 2 == player.x && height + 1 == player.y)
			|| (width + 2 == player.x && height - 1 == player.y) || (width - 2 == player.x && height - 1 == player.y)
			|| (width + 1 == player.x && height + 2 == player.y) || (width - 1 == player.x && height + 2 == player.y)
			|| (width + 1 == player.x && height - 2 == player.y) || (width - 1 == player.x && height - 2 == player.y)
			|| (width + 2 == player.x && height + 2 == player.y) || (width - 2 == player.x && height + 2 == player.y)
			|| (width + 2 == player.x && height - 2 == player.y) || (width - 2 == player.x && height - 2 == player.y))
		{
			gameState = LOSE;
		}
	}
}

void enemyDraw(int tileSize)
{
	//getting array bounds
	int Horizontal_Tile = returnBounds(tileSize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;

	CP_Settings_NoStroke();

	for (width = 0; width < Vertical_Tile; width++)
	{
		for (height = 0; height < Horizontal_Tile; height++)
		{
			if (enemies[width][height].isActive)
			{
				switch (enemies[width][height].type)
				{
				case FOUR_WAY_LOOK:
					drawBounds(1, 0, width, height, enemies[width][height].range, tileSize, 0);
					drawBounds(-1, 0, width, height, enemies[width][height].range, tileSize, 0);
					drawBounds(0, 1, width, height, enemies[width][height].range, tileSize, 0);
					drawBounds(0, -1, width, height, enemies[width][height].range, tileSize, 0);
					CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255)); //setting stroke color
					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));   //setting tile color
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					break;
				case AOE_VIEW:
					drawBounds(0, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255)); //setting stroke color
					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));   //setting tile color
					//CP_Graphics_DrawRect(width * tileSize, height * tileSize, tileSize, tileSize);
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					break;
				case DIAGONAL_LOOK:
					drawBounds(1, 1, width, height, enemies[width][height].range, tileSize, 0);
					drawBounds(1, -1, width, height, enemies[width][height].range, tileSize, 0);
					drawBounds(-1, 1, width, height, enemies[width][height].range, tileSize, 0);
					drawBounds(-1, -1, width, height, enemies[width][height].range, tileSize, 0);
					CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255)); //setting stroke color
					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));   //setting tile color
					//CP_Graphics_DrawRect(width * tileSize, height * tileSize, tileSize, tileSize);
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					break;
				}
			}
		}
	}
}

void enemyFOV(tileSize)
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
					case FOUR_WAY_LOOK:
					//checks to the right of the enemy
					if (width - player.x > 0 && player.y == height)
					{
						if (abs(width - player.x) <= enemyBounds(1, 0, width, height, enemies[width][height].range))
						{
							gameState = LOSE;
						}
					}
					//checks to the left of the enemy
					if (width - player.x < 0 && player.y == height)
					{

						if (abs(width - player.x) <= enemyBounds(-1, 0, width, height, enemies[width][height].range))
						{
							gameState = LOSE;
						}
					}

					//checks to the bottom of the enemy
					if (player.x == width && height - player.y > 0)
					{
						if (abs(height - player.y) <= enemyBounds(0, -1, width, height, enemies[width][height].range))
						{
							gameState = LOSE;
						}
					}

					//checks to the top of the enemy
					if (player.x == width && height - player.y < 0)
					{
						if (abs(height - player.y) <= enemyBounds(0, 1, width, height, enemies[width][height].range))
						{
							gameState = LOSE;
						}
					}
					break;
				case AOE_VIEW:
					aoeFOV(width, height, tileSize, enemies[width][height].isActive);
					break;
				case DIAGONAL_LOOK:
					//checks to the right of the enemy
					if (abs(width - player.x) <= enemyBounds(1, 1, width, height, enemies[width][height].range))
					{
						gameState = LOSE;
					}
					
					//checks to the left of the enemy
					if (abs(width - player.x) <= enemyBounds(-1, 1, width, height, enemies[width][height].range))
					{
						gameState = LOSE;
					}


					//checks to the bottom of the enemy
					if (abs(height - player.y) <= enemyBounds(1, -1, width, height, enemies[width][height].range))
					{
						gameState = LOSE;
					}

					//checks to the top of the enemy

					if (abs(height - player.y) <= enemyBounds(-1, -1, width, height, enemies[width][height].range))
					{
						gameState = LOSE;
					}

					break;
				}
			}
		}
	}
}

//at end, make gamestate = LOSE;
