#pragma once
#define WINIDOW_HEIGHT 800  //decide on a size but i think 800 is good 
#define WINDOW_WIDTH 1000
#define TILE_SIZE 80 //might need to make it changable depending on the stage how many tiles we want.

#define HORIZONTAL_COUNT  WINDOW_WIDTH/TILE_SIZE
#define VERTICAL_COUNT  WINIDOW_HEIGHT/TILE_SIZE

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

CP_Color Green,Red,Blue;

void game_init(void);
void game_update(void);
void game_exit(void);
void renderGame(void);

Tile tiles[HORIZONTAL_COUNT][VERTICAL_COUNT];
