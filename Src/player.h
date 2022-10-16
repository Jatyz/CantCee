#pragma once

#define playerWidth 50
#define playerHeight 50

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

typedef struct {
	int x; //current tile in x axis + 1
	int y; //current tile in y axis + 1
	int height;
	int width;

}Player;

void drawPlayer();
void setPlayerStartPoint();
Player player;
//_Bool checkMove(int x, int y);
void handlePlayerInput();