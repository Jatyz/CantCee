#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

//draws a full button that covers the screen,and there is a small panel with buttons depending on the state the button that shows up are different and does different things.
void drawFullPanel(void) {

	CP_Settings_NoStroke();
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 122));
	CP_Graphics_DrawRect(0, 0, 800, 800);

	float smallpanelx = 500, smallpanely = 400;

	float panelStartx = 400 - smallpanelx / 2;
	float panelStarty = 400 - smallpanely / 2;

	CP_Settings_Fill(CP_Color_Create(122, 122, 122, 255));
	CP_Graphics_DrawRect(panelStartx, panelStarty, smallpanelx, smallpanely);

	//for the button add switch case depending on what is the current game state
	//add a game state under game.h

	CP_Settings_RectMode(CP_POSITION_CENTER);
	switch (gameState) {
	case PAUSED:
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Settings_TextSize(70.f);
		CP_Font_DrawText("PAUSE MENU", panelStartx + 85.f, panelStarty + 60.f);
		// button 1
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 - 80, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(45.f);
		CP_Font_DrawText("Resume", panelStartx + 180, panelStarty + 135);

		// button 2
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 10, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(45.f);
		CP_Font_DrawText("Restart", panelStartx + 185, panelStarty + 225);

		//button3
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 100, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(30.f);
		CP_Font_DrawText("Level Select", panelStartx + 180, panelStarty + 310);
		break;
	case LOSE:
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Settings_TextSize(70.f);
		CP_Font_DrawText("LOSE MENU", panelStartx + 85.f, panelStarty + 60.f);
		// button 1
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 - 80, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(45.f);
		CP_Font_DrawText("Restart", panelStartx + 180, panelStarty + 135);

		// button 2
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 10, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(30.f);
		CP_Font_DrawText("Level Select", panelStartx + 185, panelStarty + 225);
		break;
	case WIN:
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Settings_TextSize(70.f);
		CP_Font_DrawText("WIN MENU", panelStartx + 105.f, panelStarty + 60.f);
		// button 1
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 - 80, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(30.f);
		CP_Font_DrawText("Next Level", panelStartx + 180, panelStarty + 135);
		// button 2
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 10, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(45.f);
		CP_Font_DrawText("Restart", panelStartx + 185, panelStarty + 225);

		//button3
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 100, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(30.f);
		CP_Font_DrawText("Level Select", panelStartx + 180, panelStarty + 310);
		break;
	}
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
}

//panel width and height use whatever number you want best multiple of tile size, x and y make sure its the tile location * tile size if u want it to cover specific tiles. text[] is just a string
void drawSmallPanel(int panelWidth, int panelHeight, int x, int y, char text[]) {
	CP_Settings_Fill(CP_Color_Create(0, 0, 122, 200));

	CP_Graphics_DrawRect(x, y, panelWidth, panelHeight);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(30.f);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawTextBox(text, x, y + 20, panelWidth);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
}

//check which button the player clicked, the buttons are hard coded spots, so the input check is also hard coded area
void checkClick(void* (button1)(void), void* (button2)(void), void* (button3)(void)) {
	float smallpanelx = 500, smallpanely = 400;

	float panelStartx = 400 - smallpanelx / 2;
	float panelStarty = 400 - smallpanely / 2;


	if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
		//button 1
		if ((IsAreaClicked(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 - 80, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY())) && button1 != 0) {
			button1();
		}
		//button 2
		if ((IsAreaClicked(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 10, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY())) && button2 != 0)
			button2();
		//button 3
		if ((IsAreaClicked(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 100, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY())) && button3 != 0)
			button3();
	}
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
}

void drawSideBarLevel(char levelNumber[], int noOfStep) {

	//switch(currentStage){
	//case 1: cp_Image_draw();


	//}

	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Fill(CP_Color_Create(0,0,0,255));
	CP_Settings_TextSize(40.f);
	CP_Font_DrawTextBox(levelNumber, 810, 30, 200);

	char* number;
	number = malloc(28 + 6);
	if (number != NULL) {
		sprintf_s(number, 34, "Number of Steps: %d", noOfStep);
	}
	CP_Settings_TextSize(25.f);
	CP_Font_DrawTextBox(number, 805, 70, 200);

	free(number);
}

void drawSideBarStats() {
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_TextSize(30.f);
	CP_Font_DrawTextBox("Number of Shine", 810, 200, 200);

	char* number;
	number = malloc(12);
	if (number != NULL) {
		sprintf_s(number, 12, "%d", player.shineCount);
	}
	CP_Settings_TextSize(40.f);
	CP_Font_DrawTextBox(number, 875, 250, 200);

	if (illumMode) {
		if (number != NULL) {
			sprintf_s(number, 12, "Illum Mode");
		}
		CP_Settings_TextSize(60.f);
		CP_Font_DrawTextBox(number, 825, 350, 200);
	}

	free(number);
}