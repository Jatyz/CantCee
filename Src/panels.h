#pragma once
#include "cprocessing.h"

//draw the pause/win/lose menu
void drawFullPanel(void);


//panel width and height use whatever number you want best multiple of tile size, x and y make sure its the tile location * tile size if u want it to cover specific tiles. text[] is just a string
void drawSmallPanel(int panelWidth, int panelHeight, int x, int y, char text[]);


//Pause Resume Restart LevelSelect
//Win Next Restart LevelSelect
//Lose Restart LevelSelect 0
void checkClick(void* (button1)(void), void* (button2)(void), void* (button3)(void));

void drawSideBar(char levelNumber[], int noOfStep);