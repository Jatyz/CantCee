#pragma once

#define WINIDOW_HEIGHT 800  //decide on a size but i think 800 is good 
#define WINDOW_WIDTH 800
#define TILE_SIZE 50 //might need to make it changable depending on the stage how many tiles we want.

#define HORIZONTAL_COUNT  WINDOW_WIDTH/TILE_SIZE
#define VERTICAL_COUNT  WINIDOW_HEIGHT/TILE_SIZE


typedef enum {
	Wall, Floor, Start, End
}Tile_Type;

typedef struct {
	Tile_Type type;
	int alert; //boolean to check whether enemies checking current tile?
}Tile;

void drawTile(void);
void assignTile(void);
Tile tiles[HORIZONTAL_COUNT][VERTICAL_COUNT];