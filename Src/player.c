#include "cprocessing.h"
#include "player.h"
#include "grid.h"
#include "game.h"
#include "utils.h"
#include "enemy.h"
#include "soundEffects.h"

//global player
Player player;

//static hold timer for player button
double holdTimer = .1;

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
	case YELLOW: CP_Settings_Fill(Yellow);
		break;
	case DEFAULT: CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
		break;
	}

	//draw player
	CP_Graphics_DrawRect((player.x * tilesize) + (tilesize / 2) - player.width / 2, (player.y * tilesize) + (tilesize / 2) - player.height / 2, player.width, player.height);

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

	//set player to the latest start point
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

void playerSwitchCheck(void)
{
	//check if player is on a switch
	if (tiles[player.x][player.y].type == SWITCH_ON || tiles[player.x][player.y].type == SWITCH_OFF) {
		player.onSwitch = 1;
	}
	else {
		player.onSwitch = 0;
	}
	//if player is on switch
	if (player.onSwitch) {

		//light up the door
		for (int i = 0; i < sizeof(gates) / sizeof(gates[0]); i++) {
			//if the address of the tile the player set on matches the specific tile in the vents
			if (gates[i].Switch == &tiles[player.x][player.y]) {

				//find the number of tiles between 0 0 and the tile at your current address
				int difference = gates[i].Door - tiles;

				//get column of 2d array
				int col = difference / MAX_TILES;

				//get row of 2d array
				int row = difference % MAX_TILES;

				lightTiles(col, row, doorLightRange);
				//lightCounter++;
			}
		}
	}

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
	//while on hold reduce hold timer
	if (CP_Input_KeyDown(KEY_W) || CP_Input_KeyDown(KEY_D) || CP_Input_KeyDown(KEY_S) || CP_Input_KeyDown(KEY_A) || CP_Input_KeyDown(KEY_UP) || CP_Input_KeyDown(KEY_RIGHT) || CP_Input_KeyDown(KEY_DOWN) || CP_Input_KeyDown(KEY_LEFT)) {
		holdTimer -= CP_System_GetDt();
	}


	//when hold timer is less than 0, move. 
	//if player triggered, move
	//up
	if ((CP_Input_KeyTriggered(KEY_W) || (CP_Input_KeyDown(KEY_W) && holdTimer<0)) || (CP_Input_KeyTriggered(KEY_UP) || (CP_Input_KeyDown(KEY_UP) && holdTimer < 0))) {
		//check if out of bounds
		if (player.y > 0) {
			//check if the tile can be moved and move
			player.y -= checkMove(0, UP);
			
			//render player
			drawPlayer(Tile_Size);
			
			//check if player getting light
			giveLight();
			
			//set direction player is facing to up
			player.direction = 0; 
		}
		holdTimer = 0.12;
	}
	//right
	if ((CP_Input_KeyTriggered(KEY_D) || (CP_Input_KeyDown(KEY_D) && holdTimer < 0)) || (CP_Input_KeyTriggered(KEY_RIGHT) || (CP_Input_KeyDown(KEY_RIGHT) && holdTimer < 0))) {
		//check out of bounds
		if (player.x < Horizontal_Tile - 1) {
			//check if tile can be moved and move
			player.x += checkMove(RIGHT, 0);
			
			//render player
			drawPlayer(Tile_Size);
			
			//check if player getting light
			giveLight();
			
			//set direction player is facing to right
			player.direction = 1;		
		}
		holdTimer = 0.12;
	}

	//down
	if ((CP_Input_KeyTriggered(KEY_S) || (CP_Input_KeyDown(KEY_S) && holdTimer < 0)) || (CP_Input_KeyTriggered(KEY_DOWN) || (CP_Input_KeyDown(KEY_DOWN) && holdTimer < 0))) {
		//check out of bounds
		if (player.y < Vertical_Tile - 1) {
			//check if the tile can be moved and move
			player.y += checkMove(0, DOWN);
			
			//draw player
			drawPlayer(Tile_Size);
			
			//check if player has moved 50 steps
			giveLight();
			
			//set direction player is facing to down
			player.direction = 2;		
		}
		holdTimer = 0.12;
	}
	//left
	if ((CP_Input_KeyTriggered(KEY_A) || (CP_Input_KeyDown(KEY_A) && holdTimer < 0)) || (CP_Input_KeyTriggered(KEY_LEFT) || (CP_Input_KeyDown(KEY_LEFT) && holdTimer < 0))) {
		//check out of bounds
		if (player.x > 0) {
			//check if the tile can be moved
			if (checkMove(LEFT, 0)) {
				//move player
				player.x -= 1;
				
				//check player
				drawPlayer(Tile_Size);
				
				//check if player getting light
				giveLight();

				//set direction player is facing to left
				player.direction = 3;	
			}
		}
		holdTimer = 0.12;
	}

	//for tile movement
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
		//check if player clicked any tile
		moveTileCheck();
	}

	//illum mode
	if (CP_Input_KeyTriggered(KEY_SPACE) && player.currentStage > 9 && !player.onSwitch) {
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
		CP_Sound_PlayAdvanced(disguiseSound,0.5f, 2.0f, FALSE, CP_SOUND_GROUP_2);
		player.Player_Color = tiles[player.x + DirectionX][player.y + DirectionY].Tile_Color;
		break;
	case VENTS:
		//check if player just tped
		player.isTP = TRUE;
		//check where the player shld tp to.
		checkVents(&tiles[player.x + DirectionX][player.y + DirectionY]);

		CP_Sound_PlayAdvanced(portalSound, 0.5f, 2.0f, FALSE, CP_SOUND_GROUP_2);
		//player does not move so return false
		return FALSE;
		//if its a closed door no movements
	case CLOSED_DOOR:
		return FALSE;
		break;
		//check if player walked into a switch
	case SWITCH_ON:
		CP_Sound_PlayAdvanced(doorOpen, 0.5f, 2.0f, FALSE, CP_SOUND_GROUP_2);
	case SWITCH_OFF:
		CP_Sound_PlayAdvanced(doorClose, 0.5f, 2.0f, FALSE, CP_SOUND_GROUP_2);
	case SWITCH_OFF:
		//open and close doors
		CP_Sound_PlayAdvanced(doorClose, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
		checkGates(&tiles[player.x + DirectionX][player.y + DirectionY]);
		break;
	case END:
		//update player info for final tile moved
		player.counter++;
		player.Prev_X = player.x;
		player.Prev_Y = player.y;

		CP_Sound_PlayAdvanced(winSound, 0.5f, 2.0f, FALSE, CP_SOUND_GROUP_2);
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
	//player moved
	return TRUE;
}

//while in illum mode
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

void moveTileCheck() {
	float x, y;
	int Width, Height;
	//find the mouse clicked position
	x = (CP_Input_GetMouseX() / 800) * returnBounds(Tile_Size);
	y = (CP_Input_GetMouseY() / 800) * returnBounds(Tile_Size);

	//change the state of the cell the mouse clicked on
	//cannot put float in array, need to explicit convert to int
	Width = x;
	Height = y;


	int direction = 0;
	int tiledif;

	//check if its horizontal or vertical movements only
	if (Width == player.x) {
		//check tile difference from player
		tiledif = abs(player.y - Height);
		if (tiledif > gameFogRange) {
			//if out of range set to range
			tiledif = gameFogRange;
		}

		//check direction
		direction = (player.y - Height) < 0 ? 1 : -1;

		//move the specific number of tiles 1 tile at a time
		for (int i = 0; i < tiledif; i++) {
			//dont let player update anything
			player.y += direction * checkMove(0, direction);
			//check if counter hit a factor of 50
			giveLight();
			//check if player walked into enemy fov
			enemyFOV(Tile_Size);
			//if player vented stop moving
			if (player.isTP) {
				player.isTP = 0;
				return;
			}
		}
	}	//check if its horizontal or vertical movements only
	else if (Height == player.y) {
		//check tile difference from player
		tiledif = abs(player.x - Width);
		if (tiledif > gameFogRange) {
			//if out of range set to range
			tiledif = gameFogRange;
		}

		//check distance from player
		direction = (player.x - Width) < 0 ? 1 : -1;

		//move specific clicked number of tiles and move 1 tile at a time
		for (int i = 0; i < tiledif; i++) {
			//dont update anything else
			player.x += direction * checkMove(direction, 0);
			//check if moved by factor of 50
			giveLight();
			//check if walked into enemy fov
			enemyFOV(Tile_Size);
			//check if player walked into a vent, if so stop moving
			if (player.isTP) {
				player.isTP = 0;
				return;
			}
		}

	}

}

void lightTileCheck() {
	if (player.shineCount > 0) {
		float x, y;
		int Width, Height;
		//find the mouse clicked position
		x = (CP_Input_GetMouseX() / 800) * returnBounds(Tile_Size);
		y = (CP_Input_GetMouseY() / 800) * returnBounds(Tile_Size);

		//change the state of the cell the mouse clicked on
		//cannot put float in array, need to explicit convert to int
		Width = x;
		Height = y;

		//set tiles lit for 2 seconds
		lightTiles(Width, Height, doorLightRange);
		lightCounter = 2;
		illumMode = 0;
		//use shine
		player.shineCount--;
	}
}

void giveLight() {
	//every 50 steps give player a shine
	if (player.counter % 50 == 0) {
		player.shineCount++;
	}

}