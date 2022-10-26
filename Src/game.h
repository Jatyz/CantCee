#pragma once

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

#define LARGE 20
#define MEDIUM 50
#define SMALL 80

//GLOBAL Color variables
CP_Color Green,Red,Blue;

//game codes
void game_init(void);
void game_update(void);
void game_exit(void);

//render the player, tiles and fov
void renderGame(void);

//set the initialize values needed in the game.
void setStartGame(void);


//global tile size variable
extern int Tile_Size;
