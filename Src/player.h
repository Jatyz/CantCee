#pragma once
#include "cprocessing.h"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50


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
void drawPlayer();
void setPlayerStartPoint();
_Bool checkMove(int x, int y);
void handlePlayerInput();

