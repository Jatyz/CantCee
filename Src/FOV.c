#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "player.h"
#include <math.h>


#define FOG_MAX_X 1000
#define FOG_MAX_Y 1000
//fog grid of same size as base game to draw over the render layers as FOV, is 1 when FOV is blocked, 0 when FOV not blocked
int fog[FOG_MAX_X][FOG_MAX_Y];		


/*
TILE_SIZE
*/

//update basic logic for drawing a layer of black tiles in the level, except in a circle around the player
void setIllumination
(
	int const playerXPos,		//player's current X position on the grid
	int const playerYPos,		//player's current Y position on the grid
	int const gridSizeX,		//size of the grid in the X axis for the level, used to find the bounds required of the fog grid
	int const gridSizeY,		//size of the grid in the Y axis for the level, used to find the bounds required of the fog grid
	int const fovRadius			//the radius of the global illumination in terms of number of tiles
)
{
	//Check if grid size out of array, if is larger than acceptable, return function
	if (gridSizeX > 1000 || gridSizeY > 1000)
	{
		return;
	}

	for (int i = 0; i < gridSizeX; i++)			//for each row
	{
		for (int j = 0; j < gridSizeY; j++)		//for each column
		{
			
			//if (abs(i - playerXPos) < 4
			//	&&
			//	abs(j - playerYPos ) < 4) 

			// if in an circular area of 4 tiles around the player
			if (
				sqrt((i - playerXPos) * (i - playerXPos)+(j - playerYPos)* (j - playerYPos))
				< fovRadius)
			{
				fog[i][j] = 0;							//set fog in this tile to none
			}
			else 
			{
				fog[i][j] = 1;							//set fog in this tile to cover tile
			}
		}
	}
}

//update basic logic for not drawing fog along player's line of sight
void setPlayerFOV(
	int const playerXPos,		//player's current X position on the grid
	int const playerYPos,		//player's current Y position on the grid
	int const playerPrevPosX,	//last X axis position of player on grid
	int const playerPrevPosY,	//last Y axis position of player on grid
	int const gridSizeX,		//size of the grid in the X axis for the level, used to find the bounds required of the fog grid
	int const gridSizeY			//size of the grid in the Y axis for the level, used to find the bounds required of the fog grid
)
{	

	//Check if grid size out of array, if is larger than acceptable, return function
	if (gridSizeX >= FOG_MAX_X || gridSizeY >= FOG_MAX_Y)
	{
		return;
	}


//	int drawY,			//is one if fov is not blocked by wall, unused till further prototyping
//		drawX;			//is one if fov is not blocked by wall, unused till further prototyping

	//these will be used until there is a way to track previous action
	int posOffsetX = (playerXPos - playerPrevPosX),		//find the last player movement, values are 0/1
		posOffsetY = (playerYPos - playerPrevPosY);		//find last player movement in Y, values are 0/1

	int coneRange = 4; //assumed cone range first, make either global or defined after debug done


	// if in an circular area of 4 tiles around the player
	if (abs(posOffsetX))								//if moved in X axis
	{
		switch (posOffsetX > 0)					// if offset > 0, player looks right, else left
		{
		case 1:

			for (int i = playerXPos; i < gridSizeX; i++)				//for each row pass player to right side of screen
			{	
				//for columns on top, below and occupied by player (vertical axis)
				for (int j = playerYPos - 1;
					(j < playerPrevPosY + 2);
					j++)			
				{
					//don't set value if out of array check!
					if(
						!(j >= gridSizeY) 
						&& !(j < 0)
						&& !(i >= gridSizeX)
						&& !(i< 0))					
					{
					fog[i][j] = 0;										//set fog in this tile to none
					}
				}
			}
			break;
		default:

			for (int i = playerXPos; i >=0; i--)						//for each row pass player to the left side of the screen
			{
				//for columns on top, below and occupied by player (vertical axis)
				for (int j = playerYPos - 1;
					(j < playerPrevPosY + 2);
					j++)
				{
					//don't set value if out of array check!
					if (
						!(j >= gridSizeY) 
						&& !(j < 0)
						&& !(i >= gridSizeX)
						&& !(i < 0))					
					{
						fog[i][j] = 0;									//set fog in this tile to none
					}
				}
			}
			break;
		}
	}
	else
	{
		if(abs(posOffsetY))							//if moved in Y axis
		{
			switch (posOffsetY > 0)					// if offset > 0, player looks down
			{
			case 1:
				//for rows surrounding/close to player in horizontal axis
				for (int i = playerXPos - 1;
					(i < playerXPos + 2);
					i++)			
				{
					for (int j = playerYPos; j < gridSizeY; j++)		//for each columns pass player to bottom of screen 
					{
						//don't set value if out of array check!
						if (
							!(i >= gridSizeX) 
							&& !(i < 0)
							&& !(j >= gridSizeY)
							&& !(j < 0)
							)				
						{
							fog[i][j] = 0;								//set fog in this tile to none
						}
					}
				}
				break;
			default:
				//for rows surrounding/close to player in horizontal axis
				for (int i = playerXPos - 1;
					(i < playerXPos + 2);
					i++)			
				{
					for (int j = playerYPos; j >= 0; j--)				//for each columns pass player to bottom of screen 
					{
						//don't set value if out of array check!
						if (
							!(i >= gridSizeX)
							&& !(i < 0)
							&& !(j >= gridSizeY)
							&& !(j < 0)
							)				
						{
							fog[i][j] = 0;								//set fog in this tile to none
						}

					}
				}
				break;
			}
		}
	}

}
	
//update basic logic for not drawing fog along player's line of sight
void setPlayerFOVFunnel(
	int const playerXPos,		//player's current X position on the grid
	int const playerYPos,		//player's current Y position on the grid
	int const playerPrevPosX,	//last X axis position of player on grid
	int const playerPrevPosY,	//last Y axis position of player on grid
	int const gridSizeX,		//size of the grid in the X axis for the level, used to find the bounds required of the fog grid
	int const gridSizeY,		//size of the grid in the Y axis for the level, used to find the bounds required of the fog grid
	int const expansionFactor,	//the rate of change of the FOV cone's expansion based on grid space 
	int const coneRange			//the range of our FOV funnel
)
{
	//Check if grid size out of array, if is larger than acceptable, return function
	if (gridSizeX >= FOG_MAX_X || gridSizeY >= FOG_MAX_Y)
	{
		return;
	}

	//	int drawY,			//is one if fov is not blocked by wall, unused till further prototyping
	//		drawX;			//is one if fov is not blocked by wall, unused till further prototyping

		//these will be used until there is a way to track previous action
	int posOffsetX = (playerXPos - playerPrevPosX),		//find the last player movement, values are 0/1
		posOffsetY = (playerYPos - playerPrevPosY);		//find last player movement in Y, values are 0/1

	int currentFactor = expansionFactor;		//the current rate of the FOV cone's expansion based on grid space, used in loop

	// if in an circular area of 4 tiles around the player
	if (abs(posOffsetX))								//if moved in X axis
	{
		switch (posOffsetX > 0)							// if offset > 0, player looks right, else left
		{
		case 1:
			//for each row pass player to right side of screen, up till end of screen or the maximum cone range
			for (int i = playerXPos; i < gridSizeX && (i-playerXPos)<=coneRange; i++)
			{
				//for columns on top, below (increase addtional 1 size  based on expansion factor) and occupied by player (vertical axis)
				for (int j = playerYPos - (currentFactor/expansionFactor);
					(j < playerPrevPosY + (currentFactor / expansionFactor)+1);
					j++)
				{
					if (!(j >= gridSizeY ) 
						&& !(j < 0)
						&& !(i >= gridSizeX)
						&& !(i < 0))								//dont set value if out of array(vertical check)
					{
						fog[i][j] = 0;								//set fog in this tile to none
					}
				}

				currentFactor++;									//increase the current factor for FOV size
			}
			break;
		default:
			//for each row pass player to the left side of the screen, up till end of screen or the maximum cone range
			for (int i = playerXPos; i >= 0 && abs(i-playerXPos) <= coneRange; i--)
			{
				//for columns on top, below and occupied by player (vertical axis)
				for (int j = playerYPos - (currentFactor / expansionFactor);
					(j < playerPrevPosY + (currentFactor / expansionFactor)+1);
					j++)
				{
					if (!(j >= gridSizeY) && !(j < 0)
						&& !(i >= gridSizeX)
						&& !(i < 0))								//dont set value if out of array(vertical check)
					{
						fog[i][j] = 0;								//set fog in this tile to none
					}
				}
				currentFactor++;									//increase the current factor for FOV size
			}
			break;
		}
	}
	else
	{
		if (abs(posOffsetY))							//if moved in Y axis
		{
			switch (posOffsetY > 0)					// if offset > 0, player looks down
			{
			case 1:
				//for each columns pass player to bottom of screen, up till end of screen or the maximum cone range
				for (int j = playerYPos; j < gridSizeY && abs(j - playerYPos) <= coneRange; j++)		 
				{
					//for rows surrounding/close to player in horizontal axis
					for (int i = playerXPos - (currentFactor / expansionFactor);
						(i < playerXPos + (currentFactor / expansionFactor)+1 );
						i++)
					{	
						//dont set value if out of array!
						if (
							!(i >= gridSizeX) 
							&& !(i < 0)
							&& !(j >= gridSizeY)
							&& !(j<0))				
						{
							fog[i][j] = 0;								//set fog in this tile to none
						}
					}
					currentFactor++;									//increase the current factor for FOV size
				}
				break;

			default:
				//for each columns pass player to top of screen, up till end of screen or the maximum cone range
				for (int j = playerYPos; j >= 0 && abs(j - playerYPos) <= coneRange; j--)					
				{
					//for rows surrounding/close to player in horizontal axis
					for (int i = playerXPos - (currentFactor / expansionFactor);
					(i < playerXPos + (currentFactor / expansionFactor) + 1);
					i++)				
					{
						if (!(i >= gridSizeX) && !(i < 0))				//dont set value if out of array(horizontal check)
						{
							fog[i][j] = 0;								//set fog in this tile to none
						}

					}
					currentFactor++;									//increase the current factor for FOV size
				}
				break;
			}
		}
	}

}

//renders the most basic version of the FOV fog	
void renderFOVBasic(
	int const gridSizeX,		//size(number of horizontal elements) of grid in game level
	int const gridSizeY,		//size(number of vertical elements) of grid in game level
	int const tileSizePX		//tile size in pixels
)
{
		//Check if grid size out of array, if is larger than acceptable, return function
		if (gridSizeX >= FOG_MAX_X || gridSizeY >= FOG_MAX_Y)
		{
			return;
		}

	for (int i = 0; i < gridSizeX; i++)			//for each row
	{
		for (int j = 0; j < gridSizeY; j++)		//for each column
		{
			switch (fog[i][j]) {
				case 1:
					CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));	//set outline black	
					CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));	//set block color black
					//draw the tile
					CP_Graphics_DrawRect(i * tileSizePX, j * tileSizePX, tileSizePX, tileSizePX);
					break;
				default:
					break;
			}
		}
	}
}

