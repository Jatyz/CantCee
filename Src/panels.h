#pragma once
#include "cprocessing.h"


void drawFullPanel(void);

void drawSmallPanel(int panelWidth, int panelHeight, int x, int y, char text[]);

void checkClick(void* (button1)(void), void* (button2)(void), void* (button3)(void));

