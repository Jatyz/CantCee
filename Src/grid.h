#pragma once
#include "cprocessing.h"
//Window size is 800 x 1000
//Actual game window is 800 by 800
#define WINIDOW_HEIGHT 800
#define WINDOW_WIDTH 1000  

#define MAX_TILES 800
typedef enum { // enum for the different type of tiles
	WALL, FLOOR, START, END, DISGUISE, CLOSED_DOOR, OPENED_DOOR, SWITCH, VENTS
}Tile_Type;

typedef struct { // method to contain information of the current tile
	Tile_Type type;
	int alert; //boolean to check whether enemies checking current tile?
	CP_Color Tile_Color;
}Tile;

typedef struct {
	Tile *tile1;
	Tile *tile2;
}Vent;

typedef struct {
	Tile* Door;
	Tile* Switch;
}Gate;

//method to take tile size and draw tiles based on the tiles global variable
void drawTile(int Tile_Size);

//method to assign all values in tiles to wall.
//and then assign all values within tile size to floor
void assignTile(int Tile_Size);


//global tiles variable
// 1000 1000 is just placeholder values so we can have a large tile map
//but specific sstage tile map will need to be set by tile size.
extern Tile tiles[MAX_TILES][MAX_TILES];

extern Vent vents[10];
extern Gate gates[10];
//returns the horizontal and vertical bounds(no. of elements) in the grid to be used for the level. Assumes grid space used is square
int returnBounds(int tilesize);

void setVents();

void resetVents();

void checkVents(Tile *address);

void setGates();

void resetGates();

void checkGates(Tile* address);