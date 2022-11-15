#include "player.h"
#include "enemy.h"
#include "grid.h"
#include "game.h"
#include "FOV.h"
#include "cprocessing.h"
#include "level1.h"
#include "panels.h"
#include "levelselect.h"
#include "levelTransition.h"
#include <stdio.h>
#include <stdlib.h>

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
int Score[30];//number in array base on number of lvls 30 as placeholder for now to test writing in and out

//static variable for animation use
int levelExited = 0,
	 levelStarted = 1;

double lightCounter, tileMoveCounter;
int doorLightRange,gameFogRange,illumMode;


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
	tiles[9][6].Tile_Color = RED;
	tiles[9][4].type = DISGUISE;
	tiles[9][4].Tile_Color = BLUE;
	tiles[0][9].type = DISGUISE;
	tiles[0][9].Tile_Color = GREEN;

	vents[0].tile1 = &tiles[9][8];
	vents[0].tile2 = &tiles[0][8];

	tiles[4][5].type = WALL;
	gates[0].Door = &tiles[4][6];
	gates[0].Switch = &tiles[9][8];


	//enemies[3][10].type = VERTICAL_HORIZONTAL_LOOK;
	//enemies[3][10].isActive = 1;
	//enemies[3][10].range = 2;
	//enemies[3][10].Color = GREEN;

	//enemies[3][8].type = DIAGONAL_LOOK;
	//enemies[3][8].isActive = 1;
	//enemies[3][8].difficulty = 1;
	//enemies[3][8].range = 1;
	//enemies[3][8].Enemy_Color = Blue;
	
	//enemies[5][5].type = AOE_VIEW;
	//enemies[5][5].isActive = 1;
	//enemies[5][5].difficulty = 2;
	//enemies[5][5].Color = BLUE;

	enemies[5][6].type = AOE_VIEW;
	enemies[5][6].isActive = 1;
	enemies[5][6].difficulty = 2;
	enemies[5][6].Color = RED;

	enemies[4][9].type = AOE_VIEW;
	enemies[4][9].isActive = 1;
	enemies[4][9].difficulty = 1;
	enemies[4][9].Color = RED;

	setStartGame(Tile_Size);

	player.setFOV = 0;
	gameState = PLAY;

	readScore();
	writeScore();

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
		//FOV logic handled here
		if (player.setFOV) {
			clearFogBackground();
			//setPlayerFOVFunnel(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 2, 10);
			//setFOVFunnelWallLogic(player.x, player.y, player.direction, returnBounds(Tile_Size), returnBounds(Tile_Size), 2, 10);
			//setIlluminationAdvance(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), 5, 5);

			//Test code for *AHEM* dynamic *AHEM* style FOV independent of actual grid resolution
			//setIllumination(player.x * 6 + 3, (player.y * 6) + 3, returnBounds(Tile_Size) * 6 + 2, returnBounds(Tile_Size) * 6 + 2, 4 * 6);
			// 
			setIlluminationWallLogicOnce(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), 5);
			//End FOV logic handled area	
		}
		drawSideBarLevel("Debug level", player.counter);
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
		checkClick(startGame, startLevelSelect, 0);
		break;
	}
	
	
	// NEW CODE HERE!! UP FOR A DISCOUNT OF WHERE'S MY WEEKENDS???!!!!
	if (levelStarted)	//when level starts, 
	{	//render enter level transition animation
		levelStarted = initLevelTransition();	//returns 0 when animation is done
		if(!levelStarted)
		{
		levelExited = 1;
		setSpriteReseted();
		}
	}

	if (levelExited)	//when level exit, 
	{	//render exit level transition animation
		//levelExited = exitLevelTransition(levelExited, game_exit);	//second parameter runs when the animation is complete, returns 0 when animation is done
		if(!levelExited)
			CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
	}
}

void game_exit(void)
{
	writeScore();
}

//all the render functions
void renderGame(void) {
	drawTile(Tile_Size);
	drawPlayer(Tile_Size);
	drawEnemy(Tile_Size);
	enemyFOV(Tile_Size);
}

//Call this function after setting Tile_Size to reset things to default
void resetGame(Tile_Size) {
	wall_Vertical = CP_Image_Load("./Assets/wall_Vertical.png");

	//player color may need to move out of this method to set from the start of the stage itself
	player.Player_Color = DEFAULT;

	//setting player size and counter
	player.height = Tile_Size / 2;
	player.width = Tile_Size / 2;
	player.counter = 0;

	//setting tiles
	resetVents();
	resetGates();
	assignTile(Tile_Size);//assign all tiles
	enemyReset(Tile_Size);

	tileMoveCounter = 0;
	gameFogRange = 3;
	player.shineCount = 0;
	lightCounter = 0;
}

//resume game
void resumeGame(void)
{
	gameState = PLAY;
}

//things to set before giving controls to the player
void setStartGame(Tile_Size) {	
	setVents();
	setGates();
	setPlayerStartPoint(Tile_Size);

	//MOAR NEW CODE HERE!! FOR ANIMATIONS
	levelExited = 0, levelStarted = 1;
	setSpriteExtended();
	gameState = START_TRANSITION;	//sets the first frame to be fully black in preperation for animation transistion in,
	//reccomendation is to not allow player control till animation is done. P.S. does rendering
}

//called after finishing each floor
void writeScore() {
	FILE* output;
	//open file to write if fail to open exit game
	if (fopen_s(&output, "Assets/Score.txt", "w") != 0) {
		exit(EXIT_FAILURE);
	}
	//write every score into the text file
	for (int i = 0; i < sizeof(Score)/sizeof(Score[0]); i++) {

		fprintf(output, "%d\n", Score[i]);
	}
	//close file
	fclose(output);
}

//called after create score in main menu
void readScore() {
	FILE* output;
	//open file to read, if fail exit game
	if (fopen_s(&output, "Assets/Score.txt", "r") != 0) {
		exit(EXIT_FAILURE);
	}
	//set pointer to start of file just incase
	fseek(output,0,SEEK_SET);
	//set a fixed amount of memory to hold the score
	char buf[6];
	int i = 0;
	while (fgets(buf,6,output) && i < 30) {
		//write score into array
		sscanf_s(buf, "%d", &Score[i]);
		i++;
	}
	//close file
	fclose(output);
}

//needs to be called in main menu
void createScore() {
	FILE* output;
	//if file exist, open else
	if (fopen_s(&output, "Assets/Score.txt", "rb+") != 0) {
		//if file does not exist create
		fopen_s(&output, "Assets/Score.txt", "wb");
	}
	if (output) {
		//close opened file
		fclose(output);
	}
}

void lightTiles(int x, int y, int range) {
	int startx = x - range;
	int starty = y - range;

	//set a square area of range around the player to light up
	for (int i = 0; i <= (2 * range); i++) {
		for (int j = 0; j <= (2 * range); j++) {
			setTileHalfLit(startx + i, starty+j);
		}
	}
	
	setTileLit(x, y);
}

void drawFog(void) {
	if (player.setFOV) {
		clearFogBackground();
		setIlluminationWallLogicOnce(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), gameFogRange+1);
		renderFOVAdvance(returnBounds(Tile_Size), returnBounds(Tile_Size), Tile_Size);
	}
}

void freeImage() {
	freeMenuImages();
	freeTransitionImage();
	freeGridImages();
}