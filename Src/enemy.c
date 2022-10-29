#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "enemy.h"


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
			}
		}
	}
}


