#pragma once


//set logic to do general illumination of area around player
void setIllumination
(
	int const playerXPos,		//horizontal position of player character on the grid
	int const playerYPos,		//vertical position of player character on the grid
	int const gridSizeX,		//horizontal size of grid
	int const gridSizeY,		//vertical size of grid
	int const fovRadius			//radius of the illumination around the player
);

//set logic for line of sight of player before render
void setPlayerFOV(
	int const playerXPos,		//horizontal position of player character on the grid
	int const playerYPos,		//vertical position of player character on the grid
	int const playerPrevPosX,	//the last stored player character's previous horizontal position
	int const playerPrevPosY,	//the last stored player character's previous vertical position
	int const gridSizeX,		//horizontal size of grid
	int const gridSizeY			//vertical size of grid
);


//set logic for line of sight of player before render
void setPlayerFOVFunnel(
	int const playerXPos,		//horizontal position of player character on the grid
	int const playerYPos,		//vertical position of player character on the grid
	int const playerPrevPosX,	//the last stored player character's previous horizontal position
	int const playerPrevPosY,	//the last stored player character's previous vertical position
	int const gridSizeX,		//horizontal size of grid
	int const gridSizeY			//vertical size of grid
);

//render array of FOV based on previous logics set by other FOV functions, renders an overlay grid similiar to the movement grid
void renderFOVBasic(
	int const gridSizeX,		//size(number of horizontal elements) of grid in game level
	int const gridSizeY,		//size(number of vertical elements) of grid in game level
	int const tileSizePX		//tile size in pixels
);