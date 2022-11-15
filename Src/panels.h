#pragma once
#include "cprocessing.h"

extern CP_Image pauseScreen;

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


//Pause Resume Restart LevelSelect
//Win Next Restart LevelSelect
//Lose Restart LevelSelect 0
void checkClick(void* (button1)(void), void* (button2)(void), void* (button3)(void));

void drawSideBarLevel(char levelNumber[], int noOfStep);

void drawSideBarPar(int noOfStep);

void drawSideBarStats();

void freeMenuImages();