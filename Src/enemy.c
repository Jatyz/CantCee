#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "enemy.h"
<<<<<<< Updated upstream


void drawEnemy(int tilesize) 
{
	CP_Settings_Fill(enemies.Enemy_Color);
	CP_Graphics_DrawRect((enemies.x * tilesize) + (tilesize / 2) - enemies.width / 2, (enemies.y * tilesize) + (tilesize / 2) - enemies.height / 2, enemies.width, enemies.height);
}

void setEnemyPoint(int tilesize)
{
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;

	int y, x;

	//do a check to see there is only one start point
	for (y = 0; y < Horizontal_Tile; y++)
	{
		for (x = 0; x < Vertical_Tile; x++)
		{
			if (tiles[x][y].type == START)
			{
				enemies.x = x;
				enemies.y = y;
=======
#include "player.h"
#include <math.h>

Enemy enemies[MAX_TILES][MAX_TILES];


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
					CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255)); //setting stroke color
					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));   //setting tile color
					CP_Graphics_DrawRect(width * tileSize, height * tileSize, tileSize, tileSize);
					break;
				case AOE_VIEW:
					CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255)); //setting stroke color
					CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));   //setting tile color
					CP_Graphics_DrawRect(width * tileSize, height * tileSize, tileSize, tileSize);
					break;
				}
>>>>>>> Stashed changes
			}
		}
	}
}

<<<<<<< Updated upstream

=======
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
				int wallX = width;
				int wallY = height;

				switch (enemies[width][height].type)
				{
				case TWO_WAY_LOOK:
					for (int i = 0; i <=4; i++)
					{
						if (width + i <= returnBounds(tileSize) && tiles[width + i][height].type == WALL)
						{
							wallX = width + i;
							break;
						}
						if (width - i == player.x && height == player.y)
						{
							//kill player here for shanding in FOV
							gameState = LOSE;
							break;
						}
						if ( width - i >= 0 && tiles[width - i][height].type == WALL)
						{
							wallX = width - i;
							break;
						}
					}
					if (abs(player.x)>abs(wallX)) 
					{
						break;
					}
					for (int i = 0; i <=4; i++)
					{
						if (height + i <= returnBounds(tileSize) && tiles[width][height + i].type == WALL)
						{
							wallY = height + i;
							break;
						}
						//
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

					break;
				}
			}
		}
	}
}

//at end, make gamestate = LOSE;
>>>>>>> Stashed changes
