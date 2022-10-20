#include "cprocessing.h"
#include "player.h"
#include "grid.h"
#include "game.h"

void drawPlayer(int Tile_Size) {
	CP_Settings_Fill(player.Player_Color);
	CP_Graphics_DrawRect((player.x * Tile_Size) + (Tile_Size / 2) - player.width / 2, (player.y * Tile_Size) + (Tile_Size / 2) - player.height / 2, player.width, player.height);
}

void setPlayerStartPoint(int Tile_Size)
{
	int Horizontal_Tile = 800 / Tile_Size;
	int Vertical_Tile = 800 / Tile_Size;

	int y, x;

	//do a check to see there is only one start point

	for (y = 0; y < Horizontal_Tile; y++) {
		for (x = 0; x < Vertical_Tile; x++) {
			if (tiles[x][y].type == START) {
				player.x = x;
				player.y = y;
			}
		}
	}
}

void handlePlayerInput(int Tile_Size) {

	int Horizontal_Tile = 800 / Tile_Size;
	int Vertical_Tile = 800 / Tile_Size;

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
	}
	//right
	if (CP_Input_KeyTriggered(KEY_D)) {
		//check out of bounds
		if (player.x < Horizontal_Tile - 1) {
			player.x += checkMove(RIGHT, 0);
		//player.x += 1;

		}
	}

	//down
	if (CP_Input_KeyTriggered(KEY_S)) {
		//check out of bounds
		if (player.y < Vertical_Tile - 1) {
			player.y += checkMove(0, DOWN);
			//player.y += 1;
		}
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
	}

}


_Bool checkMove(int DirectionX, int DirectionY) {
	//if tile is wall, player not allowed to move
	switch (tiles[player.x + DirectionX][player.y + DirectionY].type) {
	case WALL:
		return FALSE;
	case GREEN:
		player.Player_Color = Green;
		break;
	case BLUE:
		player.Player_Color = Blue;
		break;
	case RED:
		player.Player_Color = Red;
		break;
	}
	player.counter++;
	player.Prev_X = player.x;
	player.Prev_Y = player.y;
	return TRUE;

}