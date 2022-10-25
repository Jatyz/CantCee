#include "cprocessing.h"
#include "player.h"
#include "grid.h"
#include "game.h"

Player player;

void drawPlayer(int tilesize) {
	CP_Settings_StrokeWeight(0.75f);
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(player.Player_Color);
	CP_Graphics_DrawRect((player.x * tilesize) + (tilesize / 2) - player.width / 2, (player.y * tilesize) + (tilesize / 2) - player.height / 2, player.width, player.height);
	CP_Settings_NoStroke();

}

void setPlayerStartPoint(int tilesize)
{
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;
	
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

//sets the direction the player is looking in, 0 is up, 1 is right, 2 is down, 3 is left.
void setPlayerDirection(int directionFacing) 
{	//set player direction based of absoulute parameter(ensure no negatives) mod by 4 to get result within 0 to 3 
	player.direction = (directionFacing % 4); 
}

void handlePlayerInput(int tilesize) {

	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;

	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_Terminate();
	}
	//up
	if (CP_Input_KeyTriggered(KEY_W)) {
		//check if out of bounds
		if (player.y > 0) {
			//player.y -= 1;
			player.y -= checkMove(0, UP);
			player.direction = 0;		//set direction player is facing to up
		}
	}
	//right
	if (CP_Input_KeyTriggered(KEY_D)) {
		//check out of bounds
		if (player.x < Horizontal_Tile - 1) {
			player.x += checkMove(RIGHT, 0);
		//player.x += 1;
			player.direction = 1;		//set direction player is facing to right
		}
	}

	//down
	if (CP_Input_KeyTriggered(KEY_S)) {
		//check out of bounds
		if (player.y < Vertical_Tile - 1) {
			player.y += checkMove(0, DOWN);
			player.direction = 2;		//set direction player is facing to down
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
				player.direction = 3;	//set direction player is facing to left
			}
		}
	}


	//code for FOV turn without movement
	//use setPlayerDirection function to prevent an overflow of logic for int variable as setPlayerDirection 
	//warps to 0 if params are out of logic values 

	//rotate FOV +90degrees clockwise : press E 
	if (CP_Input_KeyTriggered(KEY_E)) {
		setPlayerDirection(player.direction + 1);				//set direction to 90 degrees clockwise
	}

	//rotate FOV +90degrees counter clockwise : press Q
	if (CP_Input_KeyTriggered(KEY_Q)) {
		if (player.direction - 1 < 0) { setPlayerDirection(3); }	//set direction to maximum possible value to warp negative values
		else {setPlayerDirection(player.direction - 1);}		//set direction to 90 degrees counter clockwise
	}
}


_Bool checkMove(int DirectionX, int DirectionY) {
	//if tile is wall, player not allowed to move
	switch (tiles[player.x + DirectionX][player.y + DirectionY].type) {
	case WALL:
		return FALSE;
	case DISGUISE:
		player.Player_Color = tiles[player.x + DirectionX][player.y + DirectionY].Tile_Color;
		break;
	}
	player.counter++;
	player.Prev_X = player.x;
	player.Prev_Y = player.y;
	return TRUE;
}