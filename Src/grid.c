#include "cprocessing.h"
#include "grid.h"



void grid_init(void)
{

}

void grid_update(void)
{

}



void grid_exit(void)
{

}


void drawTile() {

	int height, width;
	//for loop to go through all the tiles
	for (height = 0; height < horizontal_count; height++) {

		for (width = 0; width < vertical_count; width++) {
			//depending on the tile the color of the tile is different
			switch (tiles[width][height].type) {
			case Wall:
				CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
				break;
			case Floor:
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				break;
			case StartPt:
				CP_Settings_Fill(CP_Color_Create(0, 255, 122, 255));
				break;
			case EndPt:
				CP_Settings_Fill(CP_Color_Create(255, 0, 122, 255));
				break;
			}
			//draw the tile
			CP_Graphics_DrawRect(width * Tile_Size, height * Tile_Size, Tile_Size, Tile_Size);
		}

	}

}

void assignTile() {
	int height, width;
	//need to check tht there is only 1 start tile
	for (height = 0; height < horizontal_count; height++) {

		for (width = 0; width < vertical_count; width++) {

			tiles[width][height].type = 0;
			//is type is floor2, need to set 2 to max
		}

	}
}
