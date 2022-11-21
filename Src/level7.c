#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level7.h"
#include "panels.h"
#include "levelSelect.h"
#include "enemy.h"
#include "levelTransition.h"

void level7_init(void)
{
	//draw window
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	// set tile size
	Tile_Size = SMALL;

	//reset all arrays and variables
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);

	tiles[9][9].type = START;
	tiles[9][8].type = WALL;
	tiles[8][8].type = WALL;
	tiles[0][0].type = END;

	tiles[7][9].type = DISGUISE;
	tiles[7][9].Tile_Color = GREEN;
	tiles[5][5].type = DISGUISE;
	tiles[5][5].Tile_Color = RED;

	enemySet(5, 8, 1, 0, AOE_VIEW, GREEN);
	enemySet(8, 6, 1, 0, AOE_VIEW, GREEN);
	//set all enemy on tile
	enemySet(5, 8, 1, 0, AOE_VIEW, GREEN);
	enemySet(8, 6, 1, 0, AOE_VIEW, GREEN);
	enemySet(3, 4, 0, 6, VERTICAL_HORIZONTAL_LOOK, 0);
	
	//set all current level values
	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 7;
}

void level7_update(void)
{
	switch (gameState) {
	case PLAY:
			//clears the screen so things can be redrawn
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));

			//check for player input
			handlePlayerInput(Tile_Size);

			//draw all game tiles
			renderGame();
			//draw side bar
			drawSideBarStats("Level 7", player.counter);
			if (player.counter < 2)
			{
				drawSmallPanel(6 * Tile_Size, 2 * Tile_Size, 1 * Tile_Size, 8 * Tile_Size, "\nDisguise tiles makes it so the enemy detection system cannot see you if you are the same color as their detection!! -->");
			}

			if (player.counter > 4 && player.counter < 15)
			{
				drawSmallPanel(4 * Tile_Size, 2 * Tile_Size, 4 * Tile_Size, 1 * Tile_Size, "\nHowever, walking into the enemy in the center will still let them detect you.");
			}
		break;
		//draw pause win and lose panel and check for button click
	case PAUSED:
		drawFullPanel();
		checkClick(startLevelSelect, startLevel7, resumeGame);
		break;
	case WIN:
		drawFullPanel();
		checkClick(startLevel8, startLevel7, startLevelSelect);
		break;
	case LOSE:
		drawFullPanel();
		checkClick(0, startLevel7, startLevelSelect);
		break;
	case START_TRANSITION:
		//clear background for transition
		CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
		if (levelStarted)	//when level starts, 
		{	//render enter level transition animation
			//render game to draw the init scene
			renderGame();
			//start the transition
			levelStarted = initLevelTransition();	//returns 0 when animation is done
			//start the game
			if (!levelStarted)
			{
				gameState = PLAY;
			}
		}
		break;
	}


}

//free game resources on exit
void level7_exit(void)
{
	freeGameResources();
}
