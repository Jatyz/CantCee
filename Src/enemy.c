#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include <math.h>


//Enemy array reset function
//> set all the enemy array structure to 0
//
//Enemy setter function
//So a function that i js pass in all the element of the structure in an enemy to set instead of writing
//Enemy[][].isactive = 1
//Enemy[][].type = whatever
//Enemy.range = whatever
//
//Can js be enemyset(x, y, active, ...)

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
		switch (enemies[enemyXPos][enemyYPos].difficulty)
		{
		case 1:
			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
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
						if (player.x == xPos && player.y == yPos)
						{
							return 1;
						}
					}
				notTrue:;
				}
			}
			break;
		case 2:
			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					if (xPos < enemyXPos)
					{
						if (yPos < enemyYPos)
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
						if (yPos == enemyYPos)
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
						if (yPos > enemyYPos)
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
				notTruee:;
				}
			}
			break;
		}
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
	switch (enemies[enemyXPos][enemyYPos].type)
	{
	case VERTICAL_HORIZONTAL_LOOK:
		for (int counter = 1; counter <= range; counter++)
		{
			if ((tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == WALL || tiles[enemyXPos + (xdir * counter)][enemyYPos + (ydir * counter)].type == CLOSED_DOOR))
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
		switch (enemies[enemyXPos][enemyYPos].difficulty)
		{
		case 1:
			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
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
						CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
						CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
						CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
						CP_Settings_NoStroke();
					}
				notTrue:;
				}
			}
			break;
		case 2:
			CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
			CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
			for (int xPos = enemyXPos - 2; xPos < (enemyXPos + 3); xPos++)
			{
				for (int yPos = enemyYPos - 2; yPos < (enemyYPos + 3); yPos++)
				{
					if (xPos < enemyXPos)
					{
						if (yPos < enemyYPos)
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
						if (yPos == enemyYPos)
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
						if (yPos > enemyYPos)
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
								CP_Settings_NoStroke();
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
					}
					else if (xPos > enemyXPos)
					{
						if (yPos < enemyYPos)
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
								CP_Settings_NoStroke();
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
								CP_Settings_NoStroke();
							}
						}
						else if (yPos > enemyYPos)
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
								CP_Settings_Stroke(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Settings_Fill(enemies[enemyXPos][enemyYPos].Enemy_Color);
								CP_Graphics_DrawCircle((xPos + 0.5) * tileSize, (yPos + 0.5) * tileSize, tileSize);
								CP_Settings_NoStroke();
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
					CP_Settings_NoFill();
					break;
				case AOE_VIEW:
					drawBounds(0, 0, width, height, enemies[width][height].range, tileSize, enemies[width][height].difficulty);
					CP_Settings_Stroke(enemies[width][height].Enemy_Color);
					CP_Settings_Fill(enemies[width][height].Enemy_Color);
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					CP_Settings_NoStroke();
					CP_Settings_NoFill();
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
						if (abs(width - player.x) <= enemyBounds(1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							if (player.Player_Color != enemies[width][height].Color)
							{
								gameState = LOSE;
							}
						}
					}
						//checks to the left of the enemy and checks if player has entered enemy's FOV
					if (width - player.x < 0 && player.y == height)
					{

						if (abs(width - player.x) <= enemyBounds(-1, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							if (player.Player_Color != enemies[width][height].Color)
							{
								gameState = LOSE;
							}
						}
					}
						//checks to the bottom of the enemy and checks if player has entered enemy's FOV
					if (player.x == width && height - player.y > 0)
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
					if (player.x == width && height - player.y < 0)
					{
						if (abs(height - player.y) <= enemyBounds(0, 1, width, height, enemies[width][height].range, enemies[width][height].difficulty))
						{
							if (player.Player_Color != enemies[width][height].Color)
							{
								gameState = LOSE;
							}
						}
					}
					break;
				case AOE_VIEW:
					//checks if player has entered enemy's FOV

					if (enemyBounds(0, 0, width, height, enemies[width][height].range, enemies[width][height].difficulty) == 1)
					{
						if (player.Player_Color != enemies[width][height].Color)
						{
							gameState = LOSE;
						}
					}
					break;
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

void enemySet(int tileSize)
{
	int Horizontal_Tile = returnBounds(tileSize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;

	for (width = 0; width < Vertical_Tile; width++)
	{
		for (height = 0; height < Horizontal_Tile; height++)
		{
			switch (enemies[width][height].type)
			{
			case VERTICAL_HORIZONTAL_LOOK:
				enemies[width][height].isActive = 1;
				break;
			case AOE_VIEW:
				enemies[width][height].isActive = 1;
				break;
			}

		}
	}
}

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
			switch (enemies[width][height].type)
			{
			case VERTICAL_HORIZONTAL_LOOK:
				enemies[width][height].isActive = 0;
				break;
			case AOE_VIEW:
				enemies[width][height].isActive = 0;
				break;
			}

		}
	}
}
