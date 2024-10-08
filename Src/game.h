//---------------------------------------------------------
// file:	game.h
// author:	Jarran Tan Yan Zhi
// email:	jarranyanzhi.tan@digipen.edu
//
// brief:	Holdes all the definition of the game's handling functions.
//			
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright � 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once

#define UP -1
#define DOWN 1
#define RIGHT 1
#define LEFT -1

#define LARGE 20
#define MEDIUM 50
#define SMALL 80

#define Yellow CP_Color_Create(255, 255, 0, 255)
#define Blue CP_Color_Create(0, 0, 255, 255)
#define Red CP_Color_Create(200, 0, 50, 255)

typedef enum { // enum for the different type of tiles
	PLAY, PAUSED, WIN, LOSE, START_TRANSITION, EXIT_TRANSITION
}Game_State;

//GLOBAL Color variables
//CP_Color Green,Red,Blue;

//render the player, tiles and fov
void renderGame(void);

//set the initialize values needed in the game.
void resetGame(Tile_Size);

//set the starting values of the game based on what was assigned
void setStartGame(Tile_Size);

//unpause the game
void resumeGame(void);

//reading score from file
void readScore();

//writing score into file
void writeScore();

//creating score txt if it does not exist
void createScore();

//light up tiles in a square area
void lightTiles(int x, int y,int range);

//Contains all the function needed to update the stage of the FOG
void updateFog(void);

//contains all the function needed to free game resources such as images and audio
void freeGameResources(void);

//global tile size variable
extern int Tile_Size;
extern Game_State gameState;
extern int Score[];
extern double lightCounter;
extern int doorLightRange, gameFogRange,illumMode;
extern int levelExited, levelStarted;
//extern int parScore[]; see game.c

extern CP_Sound loseSound;
extern CP_Sound disguiseSound;
extern CP_Sound portalSound;
extern CP_Sound winSound;
extern CP_Sound doorOpen;
extern CP_Sound doorClose;
extern CP_Sound buttonSound;