//---------------------------------------------------------
// file:	grid.h
// author:	Jarran Tan Yan Zhi
// email:	jarranyanzhi.tan@digipen.edu
//
// sub author: Ong You Yang (youyang.o@digipen.edu)
// worked on all image related code
// 
// 
// brief:	holds all of the definition of the grid functions.
//			
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once
#include "cprocessing.h"
#include "player.h"

//Window size is 800 x 1000
//Actual game grid is 800 by 800
#define WINIDOW_HEIGHT 800
#define WINDOW_WIDTH 1000  

//max number of tiles possible at once.
#define MAX_TILES 800

typedef enum { // enum for the different type of tiles
	WALL, FLOOR, START, END, DISGUISE, CLOSED_DOOR, OPENED_DOOR, SWITCH_ON, SWITCH_OFF, VENTS
}Tile_Type;

typedef struct { // method to contain information of the current tile
	Tile_Type type;
	Color Tile_Color;
}Tile;

typedef struct {
	Tile* tile1;
	Tile* tile2;
}Vent;

typedef struct {
	Tile* Door;
	Tile* Switch;
}Gate;

//method to take tile size and draw tiles based on the tiles global variable
void drawTile(int Tile_Size);

//method to reset tile to initial state based on tile_size, which is within tile area its floors, anywhere else it is walls.
void resetTile(int Tile_Size);


//global variables
extern Tile tiles[MAX_TILES][MAX_TILES];

extern Vent vents[15];
extern Gate gates[15];

extern CP_Image wallTexture;
extern CP_Image floorTexture;
extern CP_Image openedDoor;
extern CP_Image closedDoor;

extern CP_Image closedVent;
extern CP_Image switchOff;
extern CP_Image switchOn;

extern CP_Image startPlatform;
extern CP_Image endPlatform;

extern CP_Image disguiseRed;
extern CP_Image disguiseBlue;
extern CP_Image disguiseYellow;

//returns the horizontal and vertical bounds(no. of elements) in the grid to be used for the level. Assumes grid space used is square
int returnBounds(int tilesize);

//set vents based on assigned
void setVents();

//reset to vents null
void resetVents();

//check if the vents was walked on
void checkVents(Tile *address);

//set gates and switch based on assigned
void setGates();

//reset to gates to null
void resetGates();

//check if a switch was walked on
void checkGates(Tile* address);

//free grid image tiles
void freeGridImages(void);