//---------------------------------------------------------
// file:	enemy.h
// author:	Tengku Danish Ashraf Bin Tengku Azlan
// email:	t.bintengkuazlan@digipen.edu
//
// brief:	This .h file is used by other programs to call the enemy script, allowing the user to spawn
//          and set enemies in their level.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#include "cprocessing.h"
#include "player.h"
#define WINIDOW_HEIGHT 800
#define WINDOW_WIDTH 1000  
#define MAX_TILES 800


//enum is used to catagorize enemies. The enum assigned to an enemy
//will dictate it's behaviour and Fied Of View
typedef enum
{
	VERTICAL_HORIZONTAL_LOOK, AOE_VIEW
}EnemyType;


//This struct is used for ALL enemies. The various parameters are used by the enemy
//to dictate the color, Line-Of-Sight length, FOV grid size, and enemy type
typedef struct
{
	Color Color;//------------------------------------------------------------------------------Used to set the player's color.
	int isActive;//-----------------------------------------------------------------------------0 is not active, all other values is active.
	int difficulty;//---------------------------------------------------------------------------used by the AOE View Enemy. Tells the program if the enemy has a 3x3 or 5x5 FOV grid.
	int range;//--------------------------------------------------------------------------------Used by the Vertical & Horizontal View Enemy. It will adjust the length of the line-of-sight.
	EnemyType type;//---------------------------------------------------------------------------Will tell the game what type an enemy is.
}Enemy;

extern Enemy enemies[MAX_TILES][MAX_TILES];//---------------------------------------------------Used externally to determine the enemy's [x] and [y] position

void drawEnemy(float tileSize);//-----------------------------------------------------------------Draws all the enemies on the level
void enemyFOV(float tileSize);//------------------------------------------------------------------Handles the general FOV logic
void enemyReset(float tileSize);//----------------------------------------------------------------Resets the enemeis on level clear
void enemySet(int width, int height, int difficulty, int range, EnemyType type, Color Color);//-Catch-all function to make it easier to load all enemy stats and parameters
