#pragma once
#define WINIDOW_HEIGHT 800  //decide on a size but i think 800 is good 
#define WINDOW_WIDTH 1000

typedef enum {
	WALL, FLOOR, START, END, RED, BLUE, GREEN
}Tile_Type;

typedef struct {
	Tile_Type type;
	int alert; //boolean to check whether enemies checking current tile?
}Tile;

void drawTile(int Tile_Size);
void assignTile(int Tile_Size);

Tile tiles[1000][1000];