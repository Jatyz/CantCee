//---------------------------------------------------------
// file:	player.h
// author:	Jarran Tan Yan Zhi
// email:	jarranyanzhi.tan@digipen.edu
// brief:	player header that holds all the definition for player related code.
//			
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "cprocessing.h"

typedef enum {
	RED,GREEN,BLUE,DEFAULT
}Color;

typedef struct { // structure to contain player variables
	int x; //current tile in x axis + 1
	int y; //current tile in y axis + 1
	int Prev_X;
	int Prev_Y;
	int direction;//store the direction the player is looking in, 0 is up, 1 is right, 2 is down, 3 is left. mod by 4 to keep from exceeding bounds required for logics
	int height;
	int width;
	int counter;//count number of stage;
	int setFOV;
	int currentStage;
	int isTP;
	int	shineCount;
	int onSwitch;
	Color Player_Color;
}Player;

//Global player variable
extern Player player;

//method to draw player in the middle of current tile, based on its own size and tile size.
void drawPlayer(int tilesize);

//method to set player to the current start point in the tile arrray
void setPlayerStartPoint(int tilesize);

//check if player is moving into a tile that is not a wall. if player moe onto color, change player color.
_Bool checkMove(int x, int y);

//handle player movements based on keyboard.
void handlePlayerInput(int Tile_Size);
void handlePlayerIllumInput();
//check to move player to a specific tile
void moveTileCheck();

//check to light up a specific tile area
void lightTileCheck();
//give player a light every 50 tiles player moved

//count how many steps the player took and give a shine accordingly
void giveShine();

//sets the player's facing direction: 0 is up, 1 is right, 2 is down, 3 is left. 
//Has in-built error warping. Numbers 4 and above are warpped via modulo of 4
void setPlayerDirection(int directionFacing);

//check if player is standing on a switch currently.
void playerSwitchCheck(void);