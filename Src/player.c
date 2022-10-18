#include "cprocessing.h"
#include "player.h"
#include "grid.h"
#include "game.h"

void drawPlayer() {
	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
	CP_Graphics_DrawRect((player.x * TILE_SIZE) + (TILE_SIZE / 2) - PLAYER_WIDTH / 2, (player.y * TILE_SIZE) + (TILE_SIZE / 2) - PLAYER_HEIGHT / 2, player.width, player.height);
}

void setPlayerStartPoint()
{
	int y, x;

	for (y = 0; y < HORIZONTAL_COUNT; y++) {
		for (x = 0; x < VERTICAL_COUNT; x++) {
			if (tiles[x][y].type == START) {
				player.x = x;
				player.y = y;
			}
		}
	}
}

void handlePlayerInput() {


	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_Terminate();
	}
	//up
	if (CP_Input_KeyTriggered(KEY_W)) {
		//check if out of bounds
		if (player.y > 0) {
			//player.y -= 1;
			player.y -= checkMove(0, UP);
		}
		renderGame();
	}
	//right
	if (CP_Input_KeyTriggered(KEY_D)) {
		//check out of bounds
		if (player.x < HORIZONTAL_COUNT - 1) {
			player.x += checkMove(RIGHT, 0);
		//player.x += 1;

		}
		renderGame();
	}

	//down
	if (CP_Input_KeyTriggered(KEY_S)) {
		//check out of bounds
		if (player.y < VERTICAL_COUNT - 1) {
			player.y += checkMove(0, DOWN);
			//player.y += 1;
		}
		renderGame();
	}
	//left
	if (CP_Input_KeyTriggered(KEY_A)) {
		//check out of bounds
		if (player.x > 0) {
			//player.x -= 1;
			if (checkMove(LEFT, 0)) {
				player.x -= 1;
			}
		}
		renderGame();
	}

}


_Bool checkMove(int DirectionX, int DirectionY) {
	//if tile is wall, player not allowed to move
	if (tiles[player.x + DirectionX][player.y + DirectionY].type == 0)
	{
		return FALSE;		
	}
	player.counter++;
	player.Prev_X = player.x;
	player.Prev_Y = player.y;
	return TRUE;
}