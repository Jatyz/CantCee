#include "cprocessing.h"
#include "utils.h"


#include "mainmenu.h"
#include "howToPlay.h"
#include "options.h"



void play_Init()
{
	// Set the window size to a sqaure 800 x 800
	CP_System_SetWindowSize(windowWidth, windowHeight);

	// Set the rectangle drawing mode to CENTER
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// All Text size
	CP_Settings_TextSize(20.0f);

	// All Text allignment
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}


// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void play_Update()
{
	// Background: Grey Colour
	CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 255));

	// -----Play Button-----
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect((windowWidth / 2.0f - 150), (windowHeight / 2.0f - 150), buttonWidth, buttonHeight);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("1", (windowWidth / 2.0f - 150), (windowHeight / 2.0f) - 150);

	// -----How to Play-----
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect((windowWidth / 2.0f - 50), (windowHeight / 2.0f - 50), buttonWidth, buttonHeight);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("2", (windowWidth / 2.0f -50), (windowHeight / 2.0f) - 50);

	// -----Options-----
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect((windowWidth / 2.0f + 50), (windowHeight / 2.0f + 50), buttonWidth, buttonHeight);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("3", (windowWidth / 2.0f + 50), (windowHeight / 2.0f) + 50);

	// -----Exit Button-----
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect((windowWidth / 2.0f + 150), (windowHeight / 2.0f) + 150, buttonWidth, buttonHeight);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("4", (windowWidth / 2.0f + 150), (windowHeight / 2.0f) + 150);



	// ---------------------------------------------------------------Mouse Inputs/Checking---------------------------------------------------------------
		// -----Checking for MouseInput-----
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		// -----Level 1 Input-----
		if (IsAreaClicked((windowWidth / 2.0f - 150), (windowHeight / 2.0f) - 150, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit); // play.c > goes to level select > click level to play
		}

		// -----How to Play Input-----
		if (IsAreaClicked((windowWidth / 2.0f - 50), (windowHeight / 2.0f) - 50, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
			//CP_Engine_SetNextGameStateForced(howToPlay_Init, howToPlay_Update, howToPlay_Exit); // change to an addition howToPlay.c
		}

		// -----Options Input-----
		if (IsAreaClicked((windowWidth / 2.0f + 50), (windowHeight / 2.0f) + 50, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
			//CP_Engine_SetNextGameStateForced(options_Init, options_Update, options_Exit); // change to an addition options.c
		}

		// -----Exit Button Input-----
		if (IsAreaClicked((windowWidth / 2.0f + 150), (windowHeight / 2.0f) + 150, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_Terminate();
		}
	}
}


// ---------------------------------------------------------------Main Menu Exit---------------------------------------------------------------
void play_Exit()
{

}
