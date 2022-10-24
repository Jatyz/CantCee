#include "cprocessing.h"
#include "grid.h"
#include "game.h"


//axulilary functions are defined first so it wont bloody crash when in a C lang compiler!!(without header)
//returns the horizontal and vertical bounds(no. of elements) in the grid to be used for the level. Assumes grid space used is square
int returnBounds(int tilesize) {
	return (800 / tilesize);
}

void drawTile(int tilesize) {
	
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;
	//for loop to go through all the tiles
	for (height = 0; height < Horizontal_Tile; height++) {

		for (width = 0; width < Vertical_Tile; width++) {
			//depending on the tile the color of the tile is different
			switch (tiles[width][height].type) {
			case WALL:
				CP_Settings_Stroke(CP_Color_Create(125, 125, 125, 255));
				CP_Settings_Fill(CP_Color_Create(125, 125, 125, 255));
				break;
			case FLOOR:
				CP_Settings_Stroke(CP_Color_Create(75, 75, 75, 255));
				CP_Settings_Fill(CP_Color_Create(75, 75, 75, 255));
				break;
			case START:
				CP_Settings_Fill(CP_Color_Create(0, 150, 75, 255));
				break;
			case END:
				CP_Settings_Fill(CP_Color_Create(200, 0, 0, 255));
				break;
			case DISGUISE:
				CP_Settings_Fill(tiles[width][height].Tile_Color);
				break;
			}
			//draw the tile
			CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize, tilesize);
		}

	}

}

void assignTile(int tilesize) {
	int height, width;
	//need to check tht there is only 1 start tile
	for (height = 0; height < sizeof(tiles)/sizeof(tiles[0]); height++) {

		for (width = 0; width < sizeof(tiles) / sizeof(tiles[0]); width++) {
			tiles[width][height].type = 0;//set all tiles to walls
		}
	}

	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;

	for (height = 0; height < Horizontal_Tile; height++) {

		for (width = 0; width < Vertical_Tile; width++) {

			tiles[width][height].type = 1; //set everything to within map to floor
		}

	}
}

void drawGrid(int tilesize) {
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;

	CP_Settings_StrokeWeight(0.5f);
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	//draw vertical lines based on how many cells in the column
	for (int rows = 0; rows < Horizontal_Tile; rows++) {
		//draw from 0 to end of game window which is 800
		CP_Graphics_DrawLine(0.f, tilesize * rows, 800, tilesize * rows);
	}
	//draw horizontal lines based on how many cells in the row
	for (int i = 0; i < Vertical_Tile; i++) {
		//draw from 0 to end of game window which is 800
		CP_Graphics_DrawLine(tilesize * i, 0.0f, tilesize * i, 800);
	}
}