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

//global variables
int Tile_Size;
Game_State gameState;
int Score[30];//number in array base on number of lvls 30 as placeholder for now to test writing in and out
int levelExited = 0, levelStarted = 1;
double lightCounter;
int doorLightRange,gameFogRange,illumMode;

//global sound variables
CP_Sound loseSound = NULL;
CP_Sound disguiseSound = NULL;
CP_Sound portalSound = NULL;
CP_Sound winSound = NULL;
CP_Sound doorOpen = NULL;
CP_Sound doorClose = NULL;
CP_Sound buttonSound = NULL;

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
	tiles[0][9].Tile_Color = YELLOW;

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

	player.setFOV = 1;
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
		//FOV logic handled here
		if (player.setFOV) {
			drawFog();
			//End FOV logic handled area	
		}renderGame();
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
	//draw tile based on tile size
	drawTile(Tile_Size);
	//draw player based on tile size
	drawPlayer(Tile_Size);
	//draw enemy based on tile size
	drawEnemy(Tile_Size);
	//draw enemy fov based on tile size
	enemyFOV(Tile_Size);
	//if not in illum mode, if not on switch, if light counter not greater than 0
	if (!player.onSwitch && !(illumMode || lightCounter > 0)) {
		//update fog state
		updateFog();
	}
	//check if player is on the switch, if they are set area around point to be defogged
	playerSwitchCheck();
	//if player has fov on
	if (player.setFOV) {
		//draw fog
		renderFOVAdvance(returnBounds(Tile_Size), returnBounds(Tile_Size), Tile_Size);
	}

}

//Call this function after setting Tile_Size to set things to default
void resetGame(Tile_Size) {
	//assigning all images
	wallTexture = CP_Image_Load("./Assets/wallTexture.png");
	floorTexture = CP_Image_Load("./Assets/floorTexture.png");
	openedDoor = CP_Image_Load("./Assets/openedDoor.png");
	closedDoor = CP_Image_Load("./Assets/closedDoor.png");

	closedVent = CP_Image_Load("./Assets/closedVent.png");
	switchOff = CP_Image_Load("./Assets/switchOff.png");
	switchOn = CP_Image_Load("./Assets/switchOn.png");

	startPlatform = CP_Image_Load("./Assets/startPlatform.png");
	endPlatform = CP_Image_Load("./Assets/endPlatform.png");

	disguiseRed = CP_Image_Load("./Assets/disguiseRed.png");
	disguiseBlue = CP_Image_Load("./Assets/disguiseBlue.png");
	disguiseYellow = CP_Image_Load("./Assets/disguiseYellow.png");

	//assigning all sound files
	loseSound = CP_Sound_Load("./Assets/Sounds/Lose Sound.mp3");
	buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
	disguiseSound = CP_Sound_Load("./Assets/Sounds/Disguise Sound.mp3");
	portalSound = CP_Sound_Load("./Assets/Sounds/Portal Sound.mp3");
	winSound = CP_Sound_Load("./Assets/Sounds/Win Sound.mp3");
	doorOpen = CP_Sound_Load("./Assets/Sounds/Door Open.mp3");
	doorClose = CP_Sound_Load("./Assets/Sounds/Door Close.mp3");

	//setting player color to default non disguised color.
	player.Player_Color = DEFAULT;

	//setting player size and counter
	player.height = Tile_Size / 2;
	player.width = Tile_Size / 2;
	player.counter = 0;

	//resetting tile states
	resetVents();
	resetGates();
	//set all playable tiles to floor, and everything out of boundaries to walls
	resetTile(Tile_Size);
	//reset all enemies states
	enemyReset(Tile_Size);

	//resetting all variables to default values
	gameFogRange = 3;
	player.shineCount = 0;
	lightCounter = 0;
	player.onSwitch = 0;
	player.isTP = 0;

	//reset trail array on init
	resetTrails();

	//resetting animation to start
	levelExited = 0, levelStarted = 1;

	//reset the transition image
	setSpriteExtended();

	//set all scenes to transition state at the start to draw transition screen
	gameState = START_TRANSITION;
}

//resume game
void resumeGame(void)
{
	//set game state to play
	gameState = PLAY;
}

//things to set before giving controls to the player
void setStartGame(Tile_Size) {	
	//assign all vent tile to vent state
	setVents();

	//setting all switch and gate tiles to switch and gate state
	setGates();

	//moving the player location to the start tile
	setPlayerStartPoint(Tile_Size);

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

//light tiles around an area
void lightTiles(int x, int y, int range) {
	//set range of tile from center
	int startx = x - range;
	int starty = y - range;

	//set a square area of range around the player to light up
	for (int i = 0; i <= (2 * range); i++) {
		for (int j = 0; j <= (2 * range); j++) {

			//set fog state of all the tiles around the center.
			setTileHalfLit(startx + i, starty+j);
		}
	}
	
	//set fog state of center tile to be brighter
	setTileLit(x, y);
}

void updateFog(void) {
	//if player is on fov mode
	if (player.setFOV) {
		//clear fog state
		clearFogBackground();
		//if on easy mode
		if (isTrailsActive) {
			//set trails based on player
			setIlluminationTrails(player.x, player.y);
			//update trails state based on player locations
			setIlluminationWallTrailsLogic(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), gameFogRange + 1);
			return;
		}
		//update fog state based on player location
		setIlluminationWallLogicOnce(player.x, player.y, returnBounds(Tile_Size), returnBounds(Tile_Size), gameFogRange + 1);
	}
}

//free all audio files
void freeSound()
{
	//if exist free
	if(loseSound == NULL) CP_Sound_Free(&loseSound);
	if(buttonSound == NULL) CP_Sound_Free(&buttonSound);
	if(disguiseSound == NULL) CP_Sound_Free(&disguiseSound);
	if(portalSound == NULL) CP_Sound_Free(&portalSound);
	if(winSound == NULL) CP_Sound_Free(&winSound);
	if(doorOpen == NULL) CP_Sound_Free(&doorOpen);
	if(doorClose == NULL) CP_Sound_Free(&doorClose);
}

//free all audio and image in the game
void freeGameResources() {
	freeSound();
	freeMenuImages();
	freeTransitionImage();
	freeGridImages();
}