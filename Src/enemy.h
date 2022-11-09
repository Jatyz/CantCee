#pragma once
#include "cprocessing.h"
#include "player.h"
#define ENEMY_FOV 8
#define WINIDOW_HEIGHT 800
#define WINDOW_WIDTH 1000  
#define MAX_TILES 800



typedef enum
{
	VERTICAL_HORIZONTAL_LOOK, AOE_VIEW, DIAGONAL_LOOK
}EnemyType;

typedef struct
{
	CP_Color Enemy_Color;
	Color Color; //for setting current player color
	int isActive;//0 is not active, all other values is active
	int difficulty;
	int range;
	EnemyType type;
}Enemy;

extern Enemy enemies[MAX_TILES][MAX_TILES];

void drawEnemy(int tileSize);
void enemyFOV(int tileSize);
void enemyReset(int tileSize);
void enemyStats(int tileSize);
void resetEnemyStats(int tileSize);
