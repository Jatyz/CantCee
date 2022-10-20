#pragma once
#define WINIDOW_HEIGHT 800  //decide on a size but i think 800 is good 
#define WINDOW_WIDTH 1000

typedef enum { // enum for the different type of tiles
	WALL, FLOOR, START, END, RED, BLUE, GREEN
}Tile_Type;

typedef struct { // method to contain information of the current tile
	Tile_Type type;
	int alert; //boolean to check whether enemies checking current tile?
}Tile;

//method to take tile size and draw tiles based on the tiles global variable
void drawTile(int Tile_Size);

//method to assign all values in tiles to wall.
//and then assign all values within tile size to floor
void assignTile(int Tile_Size);


//global tiles variable
// 1000 1000 is just placeholder values so we can have a large tile map
//but specific sstage tile map will need to be set by tile size.
Tile tiles[1000][1000];

int returnBounds(int tilesize);