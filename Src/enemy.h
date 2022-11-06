#pragma once
#include "cprocessing.h"
#define ENEMY_FOV 8
#define WINIDOW_HEIGHT 800
#define WINDOW_WIDTH 1000  
#define MAX_TILES 800



typedef enum
{
	TWO_WAY_LOOK, AOE_VIEW
}EnemyType;

typedef struct
{
	int x; //current tile in x axis + 1
	int y; //current tile in y axis + 1
	int direction;//store the direction the player is looking in, 0 is up, 1 is right, 2 is down, 3 is left. mod by 4 to keep from exceeding bounds required for logics
	int height;
	int width;
	CP_Color Enemy_Color; //for setting current player color
	int isActive;//0 is not active, all other values is active
	EnemyType type;
}Enemy;

extern Enemy enemies[MAX_TILES][MAX_TILES];

void enemyDraw(int tileSize);
void enemyFOV(int tileSize);
