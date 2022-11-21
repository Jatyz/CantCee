#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "player.h"
#include <stdio.h>

//global image variables
CP_Image wallTexture = NULL;
CP_Image floorTexture= NULL;
CP_Image openedDoor = NULL;
CP_Image closedDoor = NULL;

CP_Image closedVent = NULL;
CP_Image switchOff = NULL;
CP_Image switchOn = NULL;

CP_Image startPlatform = NULL;
CP_Image endPlatform = NULL;

CP_Image disguiseRed = NULL;
CP_Image disguiseBlue = NULL;
CP_Image disguiseYellow = NULL;



//declaration of tiles
Tile tiles[MAX_TILES][MAX_TILES];

//hardcode max 10 sets of vents
Vent vents[15];
Gate gates[15];

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

	//making sure there is no border around draw tiles.
	CP_Settings_NoStroke();
	//setting image mode to center
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	//for loop to go through all the tiles
	for (height = 0; height < Horizontal_Tile; height++) {

		for (width = 0; width < Vertical_Tile; width++) {
			//depending on the tile the image drawn is different.
			switch (tiles[width][height].type) {
			case WALL:
				CP_Settings_Stroke(CP_Color_Create(125, 125, 125, 255)); //setting stroke color
				CP_Image_Draw(wallTexture, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case FLOOR:		
				CP_Image_Draw(floorTexture, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case START:
				CP_Image_Draw(startPlatform, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case END:
				CP_Image_Draw(endPlatform, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case DISGUISE:
				switch (tiles[width][height].Tile_Color)
				{
				case RED:
					CP_Image_Draw(disguiseRed, width * tilesize, height * tilesize, tilesize, tilesize, 255);						
					break;
				case GREEN:
					CP_Image_Draw(disguiseYellow, width * tilesize, height * tilesize, tilesize, tilesize, 255);
					break;
				case BLUE:
					CP_Image_Draw(disguiseBlue, width * tilesize, height * tilesize, tilesize, tilesize, 255);
					break;
				}		
				break;
			case VENTS:
				CP_Image_Draw(closedVent, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case CLOSED_DOOR:
				CP_Image_Draw(closedDoor, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case OPENED_DOOR:
				CP_Image_Draw(openedDoor, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case SWITCH_OFF:
				CP_Image_Draw(switchOff, width * tilesize, height * tilesize, tilesize, tilesize, 255);
				break;
			case SWITCH_ON:
				CP_Image_Draw(switchOn, width * tilesize, height * tilesize, tilesize, tilesize, 255);

				break;
			}

		}

	}
	//resetting image mode
	CP_Settings_ImageMode(CP_POSITION_CENTER);
}

//reset all the tiles to only floor and walls. to be called in stage init
void resetTile(int tilesize) {
	int height, width;

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

	//get the address of tile at 0 0
	Tile* base = tiles;

	//toggle open or close all associated doors
	for (int i = 0; i < sizeof(gates) / sizeof(gates[0]); i++) {
		//if the address of the tile the player set on matches the specific tile in the vents
		if (gates[i].Switch == address) {

			if (gates[i].Door->type == OPENED_DOOR) {
				gates[i].Door->type = CLOSED_DOOR;
			}
			else if (gates[i].Door->type == CLOSED_DOOR) {
				gates[i].Door->type = OPENED_DOOR;
			}
		}
	}

	//to change the switch
	int difference = address - base;

	//get column of 2d array
	int col = difference / MAX_TILES;

	//get row of 2d array
	int row = difference % MAX_TILES;

	//toggle between switch states for drawing purposes
	if (tiles[col][row].type == SWITCH_ON) {
		tiles[col][row].type = SWITCH_OFF;
	}
	else if (tiles[col][row].type == SWITCH_OFF) {
		tiles[col][row].type = SWITCH_ON;
	}
}

void freeGridImages() {
	CP_Image_Free(&wallTexture);
	CP_Image_Free(&floorTexture);
	CP_Image_Free(&openedDoor);
	CP_Image_Free(&closedDoor);
	CP_Image_Free(&closedVent);

	CP_Image_Free(&switchOff);
	CP_Image_Free(&switchOn);

	CP_Image_Free(&startPlatform);
	CP_Image_Free(&endPlatform);

	CP_Image_Free(&disguiseRed);
	CP_Image_Free(&disguiseBlue);
	CP_Image_Free(&disguiseYellow);
	
}