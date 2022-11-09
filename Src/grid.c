#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "player.h"
#include <stdio.h>

//declaration of tiles
Tile tiles[MAX_TILES][MAX_TILES];

//hardcode max 10 sets of vents
Vent vents[10];
Gate gates[10];
//axulilary functions are defined first so it wont bloody crash when in a C lang compiler!!(without header)
//returns the horizontal and vertical bounds(no. of elements) in the grid to be used for the level. Assumes grid space used is square
int returnBounds(int tilesize) {
	return (800 / tilesize);
}

//drawing all the tiles base on their tile type.
void drawTile(int tilesize) {
	
	//getting array bounds
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
				CP_Settings_Stroke(CP_Color_Create(125, 125, 125, 255)); //setting stroke color
				CP_Settings_Fill(CP_Color_Create(125, 125, 125, 255));   //setting tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize, tilesize); //draw tile
				break;
			case FLOOR:
				CP_Settings_NoStroke(); //turn off outline, to make grid
				CP_Settings_Fill(CP_Color_Create(75, 75, 75, 255)); // set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			case START:
				CP_Settings_Fill(CP_Color_Create(0, 150, 75, 255)); // set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			case END:
				CP_Settings_Fill(CP_Color_Create(200, 0, 0, 255)); //set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			case DISGUISE:
				CP_Settings_Fill(tiles[width][height].Tile_Color); //set tile color to specific color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); // draw tile
				break;
			case VENTS:
				CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255)); //set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			case CLOSED_DOOR:
				CP_Settings_Fill(CP_Color_Create(100, 0, 100, 255)); //set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			case OPENED_DOOR:
				CP_Settings_Fill(CP_Color_Create(200, 0, 200, 255)); //set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			case SWITCH_OFF:
				CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255)); //set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			case SWITCH_ON:
				CP_Settings_Fill(CP_Color_Create(122, 122, 0, 255)); //set tile color
				CP_Graphics_DrawRect(width * tilesize, height * tilesize, tilesize - .5f, tilesize - .5f); //draw tile
				break;
			}
			//draw the tile

		}

	}

}

//reset all the tiles to only floor and walls. to be called in stage init
void assignTile(int tilesize) {
	int height, width;
	//need to check tht there is only 1 start tile

	//loop through every single tile
	for (height = 0; height < sizeof(tiles)/sizeof(tiles[0]); height++) {

		for (width = 0; width < sizeof(tiles) / sizeof(tiles[0]); width++) {
			tiles[width][height].type = 0;//set all tiles to walls
		}
	}

	//getting the bounds of the map
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;

	//loop through all the tiles within the bounds
	for (height = 0; height < Horizontal_Tile; height++) {

		for (width = 0; width < Vertical_Tile; width++) {

			//set all tiles to type 1 which is floor
			tiles[width][height].type = 1;
		}

	}
}

//setting all the vents hard set by the programmer in the stage
void setVents() {
	//loop through all vents
	for (int i = 0; i < sizeof(vents) / sizeof(vents[0]); i++) {
		//if tile is not null, set the specific tile's tile type to vent
		if(vents[i].tile1 != NULL)
		vents[i].tile1->type = VENTS;
		if (vents[i].tile2 != NULL)
		vents[i].tile2->type = VENTS;
	}
}

//reset all the vents in the array to null. To be called on stage init
void resetVents() {

	//loop to check through all vents
	for (int i = 0; i < sizeof(vents) / sizeof(vents[0]); i++) {
		//set all tiles in vents to null
		vents[i].tile1 = NULL;
		vents[i].tile2 = NULL;
	}

}

//searching for which vents the player step on, and send them to the linking vent
void checkVents(Tile *address) {
	//loop to check through all vents
	for (int i = 0; i < sizeof(vents) / sizeof(vents[0]); i++) {
		//if the address of the tile the player set on matches the specific tile in the vents
		if (vents[i].tile1 == address) {
			
			//get the address of tile at 0 0
			Tile* base = tiles;

			//find the number of tiles between 0 0 and the tile at your current address
			int difference = vents[i].tile2 - base;

			//get column of 2d array
			int col = difference / MAX_TILES;

			//get row of 2d array
			int row = difference % MAX_TILES;

			//player settings
			player.counter++;
			player.Prev_X = player.x;
			player.Prev_Y = player.y;

			player.x = col;
			player.y = row;
			return;
		}

		if (vents[i].tile2 == address) {

			//get the address of tile at 0 0
			Tile* base = tiles;

			//find the number of tiles between 0 0 and the tile at your current address
			int difference = vents[i].tile1 - base;

			//get column of 2d array
			int col = difference / MAX_TILES;

			//get row of 2d array
			int row = difference % MAX_TILES;

			//player settings
			player.counter++;
			player.Prev_X = player.x;
			player.Prev_Y = player.y;

			player.x = col;
			player.y = row;
			return;
		}
	}
	return;
}

void setGates() {
	//loop through all gates
	for (int i = 0; i < sizeof(gates) / sizeof(gates[0]); i++) {
		//if tile is not null, set the specific tile's tile type to vent
		if (gates[i].Door != NULL)
			gates[i].Door->type = CLOSED_DOOR;
		if (gates[i].Switch != NULL)
			gates[i].Switch->type = SWITCH_OFF;
	}
}

//reset all the vents in the array to null. To be called on stage init
void resetGates() {

	//loop to check through all vents
	for (int i = 0; i < sizeof(gates) / sizeof(gates[0]); i++) {
		//set all tiles in vents to null
		gates[i].Door = NULL;
		gates[i].Switch = NULL;
	}

}

void checkGates(Tile* address) {

	for (int i = 0; i < sizeof(gates) / sizeof(gates[0]); i++) {
		//if the address of the tile the player set on matches the specific tile in the vents
		if (gates[i].Switch == address && gates[i].Switch->type == SWITCH_OFF) {
			gates[i].Switch->type = SWITCH_ON;
			gates[i].Door->type = OPENED_DOOR;
			return;
		}
		if (gates[i].Switch == address && gates[i].Switch->type == SWITCH_ON) {
			gates[i].Switch->type = SWITCH_OFF;
			gates[i].Door->type = CLOSED_DOOR;
			return;
		}
	}
}