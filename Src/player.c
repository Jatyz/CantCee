#include "cprocessing.h"
#include "player.h"
#include "grid.h"
#include "game.h"
#include "utils.h"

Player player;

//draw the player
void drawPlayer(int tilesize) {
	
	//outline for player
	CP_Settings_StrokeWeight(0.75f);
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

	//check player color
	switch (player.Player_Color) {
	case RED: CP_Settings_Fill(Red);
		break;
	case BLUE: CP_Settings_Fill(Blue);
		break;
	case GREEN: CP_Settings_Fill(Green);
		break;
	case DEFAULT: CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
		break;
	}
	//Drawing player on center of the tile
	CP_Graphics_DrawRect((player.x * tilesize) + (tilesize / 2) - player.width / 2, (player.y * tilesize) + (tilesize / 2) - player.height / 2, player.width, player.height);
	//(player.x * tilesize) + (tilesize/2)
	//player.x * tilesize is the right most of the tile the player is on
	//player.width/2 moves the player closer to the center of the tile by half of the player size

	// (player.y * tilesize) + (tilesize / 2) - player.height / 2
	// player.y * tilesize is the btm most of the tile the player is on
	// player.heght/2 moves the player closer to the center of the tile by half of the player size


	//turn off outline
	CP_Settings_NoStroke();
}

//finds the start point in the tiles, set the player position to the start point.
void setPlayerStartPoint(int tilesize)
{
	//get bounds
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;
	
	//array variables
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

//handle all player keyboard inputs
void handlePlayerInput(int tilesize) {

	//getting bounds
	int Horizontal_Tile = returnBounds(tilesize);
	int Vertical_Tile = Horizontal_Tile;

	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		//brings up pause menu
		gameState = PAUSED;
	}
	//up
	if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_UP)) {
		//check if out of bounds
		if (player.y > 0) {
			//check if the tile can be moved
			player.y -= checkMove(0, UP);
			//check if player getting light
			giveLight();
			player.direction = 0;		//set direction player is facing to up
		}
	}
	//right
	if (CP_Input_KeyTriggered(KEY_D)|| CP_Input_KeyTriggered(KEY_RIGHT)) {
		//check out of bounds
		if (player.x < Horizontal_Tile - 1) {
			//check if tile can be moved
			player.x += checkMove(RIGHT, 0);
			//check if player getting light
			giveLight();
			player.direction = 1;		//set direction player is facing to right
		}
	}

	//down
	if (CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_DOWN)) {
		//check out of bounds
		if (player.y < Vertical_Tile - 1) {
			//check if the tile can be moved
			player.y += checkMove(0, DOWN);
			//check if player has moved 50 steps
			giveLight();
			player.direction = 2;		//set direction player is facing to down
		}
	}
	//left
	if (CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_LEFT)) {
		//check out of bounds
		if (player.x > 0) {
			//check if the tile can be moved
			if (checkMove(LEFT, 0)) {
				player.x -= 1;
				//check if player getting light
				giveLight();
				player.direction = 3;	//set direction player is facing to left
			}
		}
	}

	//for tile movement
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		//check if player clicked any tile, and if they have a use of light
			moveTileCheck();
	}

	//toggle light bomb
	if (CP_Input_KeyTriggered(KEY_SPACE)) {
		//activate illumination mode, where player cannot move
		illumMode = 1;
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

//check the movements of the player, if the player is about to land on a specific tile, if it is a wall, deny movement.
_Bool checkMove(int DirectionX, int DirectionY) {
	//switch case on the tile type
	switch (tiles[player.x + DirectionX][player.y + DirectionY].type) {
	case WALL:
		//if it is a wall, do not move
		return FALSE;
	case DISGUISE:
		//set the player to the tile color
		player.Player_Color = tiles[player.x + DirectionX][player.y + DirectionY].Tile_Color;
		break;
	case VENTS:
		//check if player just tped
		player.isTP = TRUE;
		//check where the player shld tp to.
		checkVents(&tiles[player.x + DirectionX][player.y + DirectionY]);
		//player does not move so return false
		return FALSE;
		//if its a closed door no movements
	case CLOSED_DOOR:
		return FALSE;
		break;
		//check if player walked into a switch
	case SWITCH_ON:
	case SWITCH_OFF:
		checkGates(&tiles[player.x + DirectionX][player.y + DirectionY]);
		break;
	case END:
		//update player info for final tile moved
		player.counter++;
		player.Prev_X = player.x;
		player.Prev_Y = player.y;
		//check if player beat previous score
		if(Score[player.currentStage] == 0 || player.counter < Score[player.currentStage])
		Score[player.currentStage] = player.counter;
		//write into file player new score
		writeScore();
		//bring up win panel
		gameState = WIN;
		return TRUE;
		break;
	}
	//change player settings
	player.counter++;
	player.Prev_X = player.x;
	player.Prev_Y = player.y;
	return TRUE;
}

void handlePlayerIllumInput() {
	if (CP_Input_KeyTriggered(KEY_SPACE)) {
		//disable illumination mode
		illumMode = 0;
	}

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		//check if player clicked and whether it shld light up the map
		lightTileCheck();
	}

}