#pragma once

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

#define LARGE 20
#define MEDIUM 50
#define SMALL 80

#define Green CP_Color_Create(0, 255, 0, 255)
#define Blue CP_Color_Create(0, 0, 255, 255)
#define Red CP_Color_Create(255, 0, 0, 255)

typedef enum { // enum for the different type of tiles
	PLAY, PAUSED, WIN, LOSE
}Game_State;

//GLOBAL Color variables
//CP_Color Green,Red,Blue;

//game codes
void game_init(void);
void game_update(void);
void game_exit(void);

//render the player, tiles and fov
void renderGame(void);

//set the initialize values needed in the game.
void resetGame(Tile_Size);

//set the starting values of the game based on what was assigned
void setStartGame(Tile_Size);

//unpause the game
void resumeGame(void);

void readScore();
void writeScore();
void createScore();

//global tile size variable
extern int Tile_Size;
extern Game_State gameState;
extern int Score[];
//extern int parScore[]; see game.c
