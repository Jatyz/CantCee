#include "player.h"
#include "grid.h"
#include "game.h"
#include "cprocessing.h"
#include "level1.h"
#include "panels.h"
#include "levelSelect.h"
#include "levelTransition.h"

void level1_init(void)
{
	//Set window size
	CP_System_SetWindowSize(WINDOW_WIDTH, WINIDOW_HEIGHT);

	//Clear background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	//setting tile size 
	Tile_Size = SMALL;

	//reset all arrays and variables and init game resources
	resetGame(Tile_Size);

	//assign all the floors and walls
	resetTile(Tile_Size);


	//for loop to go through all the tiles
	for (int height = 0; height < returnBounds(Tile_Size); height++) {

		for (int width = 0; width < returnBounds(Tile_Size); width++) {

			if (width < 3 || width > 6) {
				tiles[width][height].type = WALL;
			}
			else {
				tiles[width][height].type = FLOOR;

			}

		}
	}

	
	tiles[5][9].type = START;
	tiles[4][0].type = END;

	//set current level values
	setStartGame(Tile_Size);
	player.setFOV = 0;
	player.currentStage = 1;

}

void level1_update(void)
{
	switch (gameState) {
	case PLAY:
			//clears the screen so things can be redrawn
			CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
			//check player input every frame
			handlePlayerInput(Tile_Size);
			//render game every frame
			renderGame();
			//draw side bar
			drawSideBarStats("Level 1", player.counter);
			
			//draw prompts
			if (player.y > 5)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 7 * Tile_Size, 6 * Tile_Size, "you can press/hold WASD/arrow keys to move.");
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 0 * Tile_Size, 6 * Tile_Size, "You can use your mouse to click left/right or up/down of the player to move or");
			}
			if (player.counter > 6)
			{
				drawSmallPanel(3 * Tile_Size, 2 * Tile_Size, 0 * Tile_Size, 1 * Tile_Size, "Get to the Exit tile to proceed to next stage");

			}
		break;
	case PAUSED:
		//draw pause panel and check for clicks
		drawFullPanel();
		checkClick(startLevelSelect, startLevel1, resumeGame);
		break;
	case WIN:
		//draw win panel and check for clicks
		drawFullPanel();
		checkClick(startLevel2, startLevel1, startLevelSelect);
		break;
	case LOSE:
		//draw lose panel and check for clicks
		drawFullPanel();
		checkClick(0, startLevel1, startLevelSelect);
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

void level1_exit(void)
{
	//free game resources
	freeGameResources();
}