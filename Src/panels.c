#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "utils.h"

//draws a full button that covers the screen,and there is a small panel with buttons depending on the state the button that shows up are different and does different things.
void drawFullPanel(void) {

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
		CP_Graphics_DrawRect(panelStartx+smallpanelx/2, panelStarty + smallpanely/2 - 80 , 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(45.f);
		CP_Font_DrawText("Resume", panelStartx + 180, panelStarty+135);

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
		CP_Font_DrawText("LOSE MENU", panelStartx + 250.f, panelStarty + 60.f);
		// button 2
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 10, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(45.f);
		CP_Font_DrawText("Restart", panelStartx + 250, panelStarty + 210);

		//button3
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 100, 150, 60);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Settings_TextSize(30.f);
		CP_Font_DrawText("Level Select", panelStartx + 250, panelStarty + 300);
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

	CP_Settings_RectMode(CP_POSITION_CORNER);
}

//panel width and height use whatever number you want, x and y make sure its the tile location * tile size if u want it to cover specific tiles. text[] is just a string
void drawSmallPanel(int panelWidth, int panelHeight, int x, int y, char text[]) {
	CP_Settings_Fill(CP_Color_Create(122, 122, 122, 200));

	CP_Graphics_DrawRect(x, y, panelWidth, panelHeight);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(30.f);
	CP_Font_DrawTextBox(text, 100, 100 + 20, panelWidth);


}

//check which button the player clicked, the buttons are hard coded spots, so the input check is also hard coded area
void checkClick(void* (currentLevel)(void),void* (nextLevel)(void)) {
	float smallpanelx = 500, smallpanely = 400;

	float panelStartx = 400 - smallpanelx / 2;
	float panelStarty = 400 - smallpanely / 2;

	int button = 0;
	//button 1
	if (IsAreaClicked(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 - 80, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		button = 1;
	}
	//button 2
	if (IsAreaClicked(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 10, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		button = 2;
	//button 3
	if (IsAreaClicked(panelStartx + smallpanelx / 2, panelStarty + smallpanely / 2 + 100, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		button = 3;

		switch (gameState)
		{
		case PAUSED:
			switch (button) {
				//resume
			case 1:
				gameState = PLAY;
				break;
				//restart
			case 2:
				currentLevel();
				break;
			case 3:
				//level select
				break;
			}
			break;
		case WIN:
			switch (button) {
			case 1:
				nextLevel();
				break;
			case 2:
				currentLevel();
				break;
			case 3:
				//level select
				break;
			}
		case LOSE:
			switch (button) {
			case 2:
				currentLevel();
				break;
			case 3:
				//level select
				break;

			}
	}
}
