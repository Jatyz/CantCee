//---------------------------------------------------------
// file:	panels.h
// author:	Jarran Tan Yan Zhi
// email:	jarranyanzhi.tan@digipen.edu
// brief:	panels header that holds all the definition for panel related code.
// 
// sub author: Ong You Yang (youyang.o@digipen.edu)
// worked on all image related code
//			
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#pragma once


#include "cprocessing.h"

#define gameWindowWidth 800.f
#define gameWindowHeight 800.f

#define gameCenterX 400.f
#define gameCenterY 400.f

// Pause Menu Title
#define pauseMenuY 400.f - 100

// Pause Menu "Select Level"
#define pMenuSelectlvlY 400.f - 50

// Pause Menu "Restart"
#define pMenuRestartY 400.f

// Pause Menu "Return To Game"
#define pMenuRtoGameY 400.f + 100

//draw the pause/win/lose menu
void drawFullPanel(void);


//panel width and height use whatever number you want best multiple of tile size, x and y make sure its the tile location * tile size if u want it to cover specific tiles. text[] is just a string
void drawSmallPanel(int panelWidth, int panelHeight, int x, int y, char text[]);


//check button inputs from the pause menu / win menu / lose menu
void checkClick(void (button1)(void), void (button2)(void), void (button3)(void));

//draw the number of steps the player took from file on the side panels of the level select
void drawSideBarLevel(char levelNumber[], int noOfStep);

//draw draw the part number of steps the player took hard coded on the side panels of the level select
void drawSideBarPar(int noOfStep);

//draw the player current stats on the side panels during the game
void drawSideBarStats(char levelNumber[], int noOfStep);

//free the images used for the pause menus
void freeMenuImages();