#pragma once


//set logic to do general illumination of area around player
void setIllumination(int const playerXPos, int const playerYPos);

//set logic for line of sight of player before render
void setPlayerFOV(int const playerXPos, int const playerYPos, int const playerPrevPosX, int const playerPrevPosY);

//render array of FOV based on previous logics set by other FOV functions, renders an overlay grid similiar to the movement grid
void renderFOVBasic(void);
