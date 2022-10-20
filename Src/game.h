#pragma once

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

#define LARGE 20
#define MEDIUM 50
#define SMALL 80


CP_Color Green,Red,Blue;

void game_init(void);
void game_update(void);
void game_exit(void);
void renderGame(void);
void setStartGame(void);

int Tile_Size;

