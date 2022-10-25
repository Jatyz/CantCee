#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "player.h"
#include <stdio.h>
//declaration of tiles
Tile tiles[1000][1000];

Vents vents[10];

//axulilary functions are defined first so it wont bloody crash when in a C lang compiler!!(without header)
//returns the horizontal and vertical bounds(no. of elements) in the grid to be used for the level. Assumes grid space used is square
int returnBounds(int tilesize) {
	return (800 / tilesize);
}

void drawTile(int tilesize) {
	
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;
	int height, width;

	CP_Settings_NoStroke();
	
	//for loop to go through all the tiles
	for (height = 0; height < Horizontal_Tile; height++) {

		for (width = 0; width < Vertical_Tile; width++) {
			//depending on the tile the color of the tile is different
			switch (tiles[width][height].type) {
			case WALL:
				CP_Settings_Stroke(CP_Color_Create(125, 125, 125, 255));
				CP_Settings_Fill(CP_Color_Create(125, 125, 125, 255));
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize, tilesize);
				break;
			case FLOOR:
				CP_Settings_NoStroke();
				CP_Settings_Fill(CP_Color_Create(75, 75, 75, 255));
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f);
				break;
			case START:
				CP_Settings_Fill(CP_Color_Create(0, 150, 75, 255));
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f);
				break;
			case END:
				CP_Settings_Fill(CP_Color_Create(200, 0, 0, 255));
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f);
				break;
			case DISGUISE:
				CP_Settings_Fill(tiles[width][height].Tile_Color);
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f);
				break;
			case VENTS:
				CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255));
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f);
				break;
			}
			//draw the tile

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

void setVents() {

	for (int i = 0; i < sizeof(vents) / sizeof(vents[0]); i++) {
		if(vents[i].tile1 != NULL)
		vents[i].tile1->type = VENTS;
		if (vents[i].tile2 != NULL)
		vents[i].tile2->type = VENTS;
	}
}

void resetVents() {

	for (int i = 0; i < sizeof(vents) / sizeof(vents[0]); i++) {
		vents[i].tile1 = NULL;
		vents[i].tile2 = NULL;
	}

}

void checkVents(Tile *address) {
	for (int i = 0; i < 10; i++) {
		if (vents[i].tile1 == address) {
			
			Tile* base = &tiles[0][0];

			int difference = vents[i].tile2 - base;

			int col = difference / 1000;

			int row = difference % 1000;

			player.counter++;
			player.Prev_X = player.x;
			player.Prev_Y = player.y;

			player.x = col;
			player.y = row;
		}

		if (vents[i].tile2 == address) {

			Tile* base = &tiles[0][0];

			int difference = vents[i].tile1 - base;
			int col = difference / 1000;

			int row = difference % 1000;

			player.counter++;
			player.Prev_X = player.x;
			player.Prev_Y = player.y;

			player.x = col;
			player.y = row;
		}
	}
	return;
}