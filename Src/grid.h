#pragma once

#define wHeight 800
#define wWidth 800
#define Tile_Size 100 //might need to make it changable

#define horizontal_count  wWidth/Tile_Size
#define vertical_count  wHeight/Tile_Size


typedef enum {
	Wall, Floor, StartPt, EndPt
}Tile_Type;

typedef struct {
	Tile_Type type;
	int Alert; //boolean to check whether enemies checking current tile?
}Tile;

void grid_init(void);
void grid_update(void);
void grid_exit(void);
void drawTile(void);
void assignTile(void);
Tile tiles[horizontal_count][vertical_count];