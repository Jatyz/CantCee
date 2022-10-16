#include "cprocessing.h"
#include "player.h"
#include "grid.h"
#include "game.h"

void drawPlayer() {
	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
	CP_Graphics_DrawRect((player.x * Tile_Size) + (Tile_Size / 2) - playerWidth / 2, (player.y * Tile_Size) + (Tile_Size / 2) - playerHeight / 2, player.width, player.height);
}

void setPlayerStartPoint()
{
	int y, x;

	for (y = 0; y < horizontal_count; y++) {
		for (x = 0; x < vertical_count; x++) {
			if (tiles[x][y].type == StartPt) {
				player.x = x;
				player.y = y;
			}
		}
	}
}

void handlePlayerInput() {


	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_Terminate();
	}//up

	if (CP_Input_KeyTriggered(KEY_W)) {
		//check if out of bounds
		if (player.y > 0) {
			player.y -= 1;
			//player.y -= checkMove(0, UP);
		}
		render_game();
	}
	//right
	if (CP_Input_KeyTriggered(KEY_D)) {
		//check out of bounds
		if (player.x < horizontal_count - 1) {
		//	player.x += checkMove(RIGHT, 0);
		player.x += 1;

		}
		render_game();
	}

	//down
	if (CP_Input_KeyTriggered(KEY_S)) {
		//check out of bounds
		if (player.y < vertical_count - 1) {
			//player.y += checkMove(0, DOWN);
			player.y += 1;
		}
		render_game();
	}
	//left
	if (CP_Input_KeyTriggered(KEY_A)) {
		//check out of bounds
		if (player.x > 0) {
			player.x -= 1;
			//if (checkMove(LEFT, 0)) {
			//	player.x -= 1;
			//}
		}
		render_game();
	}

}



_Bool checkMove(int DirectionX, int DirectionY) {
	//if tile is wall, player not allowed to move
	if (tiles[player.x + DirectionX][player.y + DirectionY].type == 0)
	{
		return FALSE;
	}

	return TRUE;
}