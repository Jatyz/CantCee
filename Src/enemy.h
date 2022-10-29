#pragma once
#include "cprocessing.h"

typedef struct { // structure to contain player variables
	int x; //current tile in x axis + 1
	int y; //current tile in y axis + 1
	int direction;//store the direction the player is looking in, 0 is up, 1 is right, 2 is down, 3 is left. mod by 4 to keep from exceeding bounds required for logics
	int height;
	int width;
	CP_Color Enemy_Color; //for setting current player color
}Enemy;