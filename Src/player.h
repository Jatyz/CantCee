#pragma once
#include "cprocessing.h"


typedef struct { // structure to contain player variables
	int x; //current tile in x axis + 1
	int y; //current tile in y axis + 1
	int Prev_X;
	int Prev_Y;
	int height;
	int width;
	int counter;//count number of stage;
	CP_Color Player_Color;
}Player;

//Global player variable
Player player;

//method to draw player in the middle of current tile, based on its own size and tile size.
void drawPlayer(int tilesize);

//method to set player to the current start point in the tile arrray
void setPlayerStartPoint(int tilesize);

//check if player is moving into a tile that is not a wall. if player moe onto color, change player color.
_Bool checkMove(int x, int y);

//handle player movements based on keyboard.
void handlePlayerInput(int Tile_Size);

