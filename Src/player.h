#pragma once

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

typedef struct {
	int x; //current tile in x axis + 1
	int y; //current tile in y axis + 1
	int height;
	int width;
	int counter;//count number of stage;
}Player;

Player player;
void drawPlayer();
void setPlayerStartPoint();
//_Bool checkMove(int x, int y);
void handlePlayerInput();