#pragma once


typedef enum {
	WALL, FLOOR, START, END, RED, BLUE, GREEN
}Tile_Type;

typedef struct {
	Tile_Type type;
	int alert; //boolean to check whether enemies checking current tile?
}Tile;

void drawTile(void);
void assignTile(void);
