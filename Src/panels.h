#pragma once
#include "cprocessing.h"


void drawFullPanel(void);

void drawSmallPanel(int panelWidth, int panelHeight, int x, int y, char text[]);

void checkClick(void* (currentLevel)(void), void* (nextLevel)(void));

