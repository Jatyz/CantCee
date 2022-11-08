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

int enemyBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range, int difficulty)
{
	switch (enemies[enemyXPos][enemyYPos].type)
	{
	case VERTICAL_HORIZONTAL_LOOK:
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
	case AOE_VIEW:
		if (difficulty == 1)
		{

			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
			for (int xPos = enemyXPos - 1; xPos < (enemyXPos + 2); xPos++)
			{
				for (int yPos = enemyYPos - 1; yPos < (enemyYPos + 2); yPos++)
				{
					int wallXPos;
					int wallYPos;
					if (tiles[xPos][yPos].type != WALL)
					{
						if (player.x == xPos && player.y == yPos)
						{
							return 1;
						}
					}

					//else if (tiles[xPos][yPos].type == WALL)
					//{
					//	wallXPos = xPos;
					//	wallYPos = yPos;
					//}
				}
			}
		}

		if (difficulty == 2)
		{
			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					int wallXPos;
					int wallYPos;
					if (tiles[xPos][yPos].type != WALL)
					{
						if (player.x == xPos && player.y == yPos)
						{
							return 1;
						}
					}
					//else if (tiles[xPos][yPos].type == WALL)
					//{
					//	wallXPos = xPos;
					//	wallYPos = yPos;
					//}
				}
			}
		}
		return 0;
		break;
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
}

void drawBounds(int xdir, int ydir, int enemyXPos, int enemyYPos, int range, int tileSize, int difficulty)
{
	Red = CP_Color_Create(255, 0, 0, 40);
	Green = CP_Color_Create(0, 255, 0, 40);
	Blue = CP_Color_Create(0, 0, 255, 40);

	switch (enemies[enemyXPos][enemyYPos].type)
	{
	case VERTICAL_HORIZONTAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
			if (tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL)
			{
				return NULL;
			}
			else
			{
				CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
				CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
				CP_Graphics_DrawCircle((enemyXPos + (xdir * counter) + 0.5) * tileSize, (enemyYPos + (ydir * counter) + 0.5) * tileSize, tileSize);
				CP_Settings_NoStroke();
			}
		}
		break;
	case AOE_VIEW:
		if (difficulty == 1)
		{

			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
			for (int xPos = enemyXPos - 1; xPos < (enemyXPos + 2); xPos++)
			{
				for (int yPos = enemyYPos - 1; yPos < (enemyYPos + 2); yPos++)
				{
					int wallXPos;
					int wallYPos;
					if (tiles[xPos][yPos].type != WALL)
					{
						CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
						CP_Settings_NoStroke();
					}

					else if (tiles[xPos][yPos].type == WALL)
					{
						wallXPos = xPos;
						wallYPos = yPos;
						if (wallXPos > enemyXPos && wallYPos < enemyYPos)
						{
							CP_Settings_NoFill();
							CP_Settings_NoStroke();
						}
					}
				}
			}
		}

		if (difficulty == 2)
		{
			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					int wallXPos;
					int wallYPos;
					if (tiles[xPos][yPos].type != WALL)
					{
						CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
						CP_Settings_NoStroke();
					}
					else if (tiles[xPos][yPos].type == WALL)
					{
						wallXPos = xPos;
						wallYPos = yPos;
					}
				}
			}
		}
		break;
	case DIAGONAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
			if (tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL)
			{
				return NULL;
			}
			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Graphics_DrawCircle((enemyXPos + (xdir * counter) + 0.5) * tileSize, (enemyYPos + (ydir * counter) + 0.5) * tileSize, tileSize);
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

	CP_Settings_NoStroke();

	for (width = 0; width < Vertical_Tile; width++)
	{
		for (height = 0; height < Horizontal_Tile; height++)
		{
			if (enemies[width][height].isActive)
			{
				switch (enemies[width][height].type)
				{
				case VERTICAL_HORIZONTAL_LOOK:
					drawBounds(1, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(-1, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(0, 1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(0, -1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					CP_Settings_Stroke(enemies[width][height].Enemy_Color);
					CP_Settings_Fill(enemies[width][height].Enemy_Color);
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					CP_Settings_NoStroke();
					break;
				case AOE_VIEW:
					drawBounds(0, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					CP_Settings_Stroke(enemies[width][height].Enemy_Color);
					CP_Settings_Fill(enemies[width][height].Enemy_Color);
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					CP_Settings_NoStroke();
					break;
				case DIAGONAL_LOOK:
					drawBounds(1, 1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(1, -1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(-1, 1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					drawBounds(-1, -1, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					CP_Settings_Stroke(enemies[width][height].Enemy_Color);
					CP_Settings_Fill(enemies[width][height].Enemy_Color);
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					CP_Settings_NoStroke();
					break;
				}
			}
		}
	}

}

void enemyReset(int tileSize)
{

	int Horizontal_Tile = returnBounds(tileSize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;

	for (int width = 0; width < Horizontal_Tile; width++)
	{
		for (int height = 0; height < Vertical_Tile; height++)
		{
			CP_Settings_NoStroke();
			CP_Settings_NoFill();
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
					case VERTICAL_HORIZONTAL_LOOK:
					//checks to the right of the enemy and checks if player has entered enemy's FOV
					if (width - player.x > 0 && player.y == height)
					{
						if (abs(width - player.x) <= enemyBounds(1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							//if (player.Player_Color == enemies[width][height].Enemy_Color)
							//{
							gameState = LOSE;
							//}
						}
					}
					//checks to the left of the enemy and checks if player has entered enemy's FOV
					if (width - player.x < 0 && player.y == height)
					{

						if (abs(width - player.x) <= enemyBounds(-1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							gameState = LOSE;
						}
					}
					//checks to the bottom of the enemy and checks if player has entered enemy's FOV
					if (player.x == width && height - player.y > 0)
					{
						if (abs(height - player.y) <= enemyBounds(0, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							gameState = LOSE;
						}
					}
					//checks to the top of the enemy and checks if player has entered enemy's FOV
					if (player.x == width && height - player.y < 0)
					{
						if (abs(height - player.y) <= enemyBounds(0, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							gameState = LOSE;
						}
					}
					break;
				case AOE_VIEW:
					//checks if player has entered enemy's FOV
					if (enemyBounds(0, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty) == 1)
					{
						gameState = LOSE;
					}
					break;
				case DIAGONAL_LOOK:
					//checks to the right of the enemy
					//if (abs(width - player.x) <= enemyBounds(1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty)
					//	&& abs(height - player.y) <= enemyBounds(0, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					//{
					//	gameState = LOSE;
					//}
					////checks to the left of the enemy
					//if (abs(width - player.x) <= enemyBounds(-1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty)
					//	&& abs(height - player.y) <= enemyBounds(0, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					//{
					//	gameState = LOSE;
					//}
					////checks to the bottom of the enemy
					//if (abs(width - player.x) <= enemyBounds(1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty)
					//	&& abs(height - player.y) <= enemyBounds(0, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					//{
					//	gameState = LOSE;
					//}
					////checks to the top of the enemy
					//if (abs(width - player.x) <= enemyBounds(-1, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty)
					//	&& abs(height - player.y) <= enemyBounds(0, -1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
					//{
					//	gameState = LOSE;
					//}
					


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
