#include "player.h"
#include "enemy.h"
#include "grid.h"
#include "game.h"
#include "FOV.h"
#include "cprocessing.h"
#include "level1.h"
#include "panels.h"
#include "levelselect.h"
/*
THE CODES UNDER GAME_INIT, GAME_UPDATE IS FOR TESTING
FOR THE REAL STAGES WE NEED TO CREATE ANOTHER C AND H FILE TO INITIALIZE AND CALL THE FILES UNDER GAME.C

IN INITIALIZE
WE WILL NEED TO INIT THE TILE MAP, UNLESS WE CAN READ FROM EDITOR AND ASSIGN USING ASSIGN TILE

SET WINDOW SIZE
CLEAR WINDOW BACKGROUND TO CLEAR RENDER

CALL SETSTARTGAME

SET PLAYER START POINT AFTER ASSIGNING TILES

*/

//DO NOT INITIALIZE ANYMORE TILES AND PLAYER VARIABLES, THEY ARE GLOBAL.
//IF YOU NEED TO ACCESS PLAYER AND TILES JUST INCLUDE THE SPEICIF HEADER FILES.

int Tile_Size;
Game_State gameState;

void game_init(void)
{
	//setting game window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//change this variable to change the number of tiles on the map X by X
	//Factors of 800
	// use these below
	// 20,25,32,40,50,80,100,160
	//e.g. large room = 20
	// medium room = 50
	// small room = 80
	Tile_Size = MEDIUM;
	
	//setting game init states
	resetGame(Tile_Size);

	//hardcode to test drawing make sure only 1 start point
	tiles[0][0].type = END;
	tiles[0][4].type = WALL;
	tiles[1][4].type = WALL;
	tiles[2][4].type = WALL;
	tiles[3][4].type = WALL;
	tiles[4][4].type = WALL;
	tiles[5][4].type = WALL;
	tiles[4][7].type = WALL;
	tiles[5][7].type = WALL;
	tiles[6][7].type = WALL;
	tiles[7][7].type = WALL;
	tiles[8][7].type = WALL;
	tiles[9][7].type = WALL;
	tiles[7][8].type = START;
	tiles[9][6].type = DISGUISE;
	tiles[9][6].Tile_Color = Red;
	tiles[9][4].type = DISGUISE;
	tiles[9][4].Tile_Color = Blue;
	tiles[0][9].type = DISGUISE;
	tiles[0][9].Tile_Color = Green;

	vents[0].tile1 = &tiles[9][0];
	vents[0].tile2 = &tiles[0][8];

	tiles[4][5].type = WALL;
	gates[0].Door = &tiles[4][6];
	gates[0].Switch = &tiles[9][8];


	enemies[3][10].type = AOE_VIEW;
	enemies[3][10].isActive = 1;

	setStartGame(Tile_Size);
	player.setFOV = 0;
	gameState = PLAY;
}

void game_update(void)
{
	//level select code
	if (CP_Input_KeyDown(KEY_F1)) {
		player.counter = 10000;
	}

	switch (gameState) {
	case PLAY:
		//clears the screen so things can be redrawn
		CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
		handlePlayerInput(Tile_Size);
		//all the game update methods that needs to be updated every frame
		renderGame();
		enemyFOV(Tile_Size);
		//FOV logic handled here
		if (player.setFOV) {
			clearFogBackground();
			//setPlayerFOVFunnel(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 2, 10);
			//setFOVFunnelWallLogic(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 2, 10);
			setIlluminationAdvance(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), 5, 5);

			//Test code for *AHEM* dynamic *AHEM* style FOV independent of actual grid resolution
			//setIllumination(player.x * 6 + 3, (player.y * 6) + 3, returnBounds(Tile_Size) * 6 + 2, returnBounds(Tile_Size) * 6 + 2, 4 * 6);
			// 
			setIlluminationWallLogic(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), 5);
			//End FOV logic handled area	
		}
		drawSideBar("Debug level",player.counter);
		break;
	case PAUSED:
		drawFullPanel();
		checkClick(resumeGame, startGame, startLevelSelect);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel1, startGame, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(startGame, startLevelSelect,0);
		break;
	}
}

void game_exit(void)
{

}

//all the render functions
void renderGame(void) {
	drawTile(Tile_Size);
	drawPlayer(Tile_Size);
	enemyDraw(Tile_Size);
	enemyFOV(Tile_Size);
	if(player.setFOV)
	renderFOVAdvance(returnBounds(Tile_Size) , returnBounds(Tile_Size) , Tile_Size);

	//Test code for *AHEM* dynamic *AHEM* style FOV independent of actual grid resolution
	//renderFOVBasic(returnBounds(Tile_Size)*6+2, returnBounds(Tile_Size)*6+2,Tile_Size/6);
	//End FOV render code
}

//Call this function after setting Tile_Size
void resetGame(Tile_Size) {

	//player color may need to move out of this method to set from the start of the stage itself
	player.Player_Color = CP_Color_Create(0, 255, 255, 255);

	//settings the colors
	Green = CP_Color_Create(0, 255, 0, 255);
	Red = CP_Color_Create(255, 0, 0, 255);
	Blue = CP_Color_Create(0, 0, 255, 255);

	//setting player size and counter
	player.height = Tile_Size / 2;
	player.width = Tile_Size / 2;
	player.counter = 0;

	//setting tiles
	resetVents();
	resetGates();
	assignTile(Tile_Size);//assign all tiles
}

void resumeGame(void)
{
	gameState = PLAY;
}

void setStartGame(Tile_Size) {
	setVents();
	setGates();
	setPlayerStartPoint(Tile_Size);
}