#pragma once
#include "cprocessing.h"


typedef struct {
	int x; //current tile in x axis + 1
	int y; //current tile in y axis + 1
	int Prev_X;
	int Prev_Y;
	int height;
	int width;
	int counter;//count number of stage;
	CP_Color Player_Color;
}Player;

Player player;
void drawPlayer(int Tile_size);
void setPlayerStartPoint(int Tile_Size);
_Bool checkMove(int x, int y);
void handlePlayerInput(int Tile_Size);

