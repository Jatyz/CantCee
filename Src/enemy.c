#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include <math.h>

Enemy enemies[MAX_TILES][MAX_TILES];

//For AOE Enemy
//(difficulty == 1) Checks 8 grids around AOE Enemy
//(difficulty == 1) Checks 20 grids around AOE Enemy
void aoeFOV(int width, int height, int tileSize, int difficulty)
{
	if (difficulty == 1)
	{
		CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 40)); //setting stroke color
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 40));   //setting tile color
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height + 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height - 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height - 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height - 0.5) * tileSize, tileSize);
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
		CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 40)); //setting stroke color
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 40));   //setting tile color
		//Inner Ring
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height + 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height - 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height - 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height - 0.5) * tileSize, tileSize);
		//Outer Ring
		CP_Graphics_DrawCircle((width + 2.5) * tileSize, (height - 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 2.5) * tileSize, (height - 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 2.5) * tileSize, (height + 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 2.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 2.5) * tileSize, (height + 2.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height + 2.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 2.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height + 2.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 1.5) * tileSize, (height - 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 1.5) * tileSize, (height - 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 1.5) * tileSize, (height + 0.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 1.5) * tileSize, (height + 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 1.5) * tileSize, (height + 2.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 1.5) * tileSize, (height - 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height - 1.5) * tileSize, tileSize);
		CP_Graphics_DrawCircle((width - 0.5) * tileSize, (height - 1.5) * tileSize, tileSize);
		if ((width + 2 == player.x && height == player.y) || (width - 2 == player.x && height == player.y)
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
				case TWO_WAY_LOOK:
					CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 150)); //setting stroke color
					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 150));   //setting tile color
					CP_Graphics_DrawCircle((width + 0.5) * tileSize, (height + 0.5) * tileSize, tileSize);
					break;
				case AOE_VIEW:
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
				int wallXPlus = width;
				int wallXMinus = width;
				int wallY = height;

				switch (enemies[width][height].type)
				{
				case TWO_WAY_LOOK:
					for (int i = 0 ; i <= 4 ; i++)
					{
						if (width + i <= returnBounds(tileSize) && tiles[width + i][height].type == WALL)
						{
							wallXPlus = width + i;
							break;
						}
						if (width - i >= 0 && tiles[width - i][height].type == WALL)
						{
							wallXMinus = width - i;
							break;
						}
						if ((wallXPlus == player.x && height == player.y) || (wallXMinus == player.x && height == player.y))
						{
							//kill player here for shanding in FOV
							gameState = LOSE;
							break;
						}
					}
					if (abs(player.x) > abs(wallXPlus)) 
					{
						break;
					}

					if (abs(player.x) < abs(wallXMinus))
					{
						break;
					}
					for (int i = 0 ; i <=4; i++)
					{
						if (height + i <= returnBounds(tileSize) && tiles[width][height + i].type == WALL)
						{
							wallY = height + i;
							break;
						}
						if ((height + i == player.y && width == player.x) || (height - i == player.y && width == player.x))
						{
							//kill player here for shanding in FOV
							gameState = LOSE;
							break;
						}
						if (height - i >= 0 && tiles[width][height - i].type == WALL)
						{
							wallY = height - i;
							break;
						}
					}
					if (abs(player.y) > abs(wallY))
					{
						break;
					}
					break;
				case AOE_VIEW:
					aoeFOV(width, height, tileSize, enemies[width][height].isActive);
					break;
				}
			}
		}
	}
}

//at end, make gamestate = LOSE;
