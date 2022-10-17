#include "cprocessing.h"
#include "grid.h"

void drawTile() {

	int height, width;
	//for loop to go through all the tiles
	for (height = 0; height < HORIZONTAL_COUNT; height++) {

		for (width = 0; width < VERTICAL_COUNT; width++) {
			//depending on the tile the color of the tile is different
			switch (tiles[width][height].type) {
			case Wall:
				CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
				break;
			case Floor:
				CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
				break;
			case Start:
				CP_Settings_Fill(CP_Color_Create(0, 255, 122, 255));
				break;
			case End:
				CP_Settings_Fill(CP_Color_Create(255, 0, 122, 255));
				break;
			}
			//draw the tile
			CP_Graphics_DrawRect(width * TILE_SIZE, height * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}

	}

}

void assignTile() {
	int height, width;
	//need to check tht there is only 1 start tile
	for (height = 0; height < HORIZONTAL_COUNT; height++) {

		for (width = 0; width < VERTICAL_COUNT; width++) {

			tiles[width][height].type = 0;
			//is type is floor2, need to set 2 to max
		}

	}
}
