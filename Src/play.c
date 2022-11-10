#include "cprocessing.h"
#include "utils.h"

#include "mainmenu.h"
#include "howToPlay.h"
#include "settings.h"
#include "levelselect.h"
#include "level1.h"

CP_Image square = NULL;

int clicked = 0;

void play_Init()
{
	// Set the window size to a sqaure 1000 x 800
	CP_System_SetWindowSize(windowWidth, windowHeight);

	// Set the rectangle drawing mode to CENTER
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// All Text size
	CP_Settings_TextSize(20.0f);

	// All Text allignment
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	square = CP_Image_Load("./Assets/square.png");

}


// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void play_Update()
{
	// Background: Grey Colour
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	if (clicked == 0) {
		// -----Level 1-----
		CP_Image_Draw(square, windowWidth / 2, windowHeight / 2, levelButtonWidth, levelButtonHeight, 255);
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect((windowWidth / 2.0f - 100), (windowHeight / 2.0f - 100), levelButtonWidth, levelButtonHeight);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("1", (windowWidth / 2.0f - 100), (windowHeight / 2.0f - 100));

		// -----Level 2-----
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect((windowWidth / 2.0f + 100), (windowHeight / 2.0f - 100), levelButtonWidth, levelButtonHeight);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("2", (windowWidth / 2.0f + 100), (windowHeight / 2.0f - 100));

		// -----Level 3-----
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect((windowWidth / 2.0f - 100), (windowHeight / 2.0f + 100), levelButtonWidth, levelButtonHeight);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("3", (windowWidth / 2.0f - 100), (windowHeight / 2.0f + 100));

		// -----Level 4-----
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawRect((windowWidth / 2.0f + 100), (windowHeight / 2.0f + 100), levelButtonWidth, levelButtonHeight);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
		CP_Font_DrawText("4", (windowWidth / 2.0f + 100), (windowHeight / 2.0f + 100));

	}

	// -----Level 5-----
	//CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	//CP_Graphics_DrawRect((windowWidth / 2.0f + 250), (windowHeight / 2.0f), levelButtonWidth, levelButtonHeight);
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Font_DrawText("5", (windowWidth / 2.0f + 250), (windowHeight / 2.0f));



	// ---------------------------------------------------------------Mouse Inputs/Checking---------------------------------------------------------------
		// -----Checking for MouseInput-----
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1) {
		if (IsAreaClicked((windowWidth / 2.0f - 100), (windowHeight / 2.0f - 100), levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			clicked = 1;
		}

	}

		// -----Level 1 Input-----
		if (clicked == 1)
		{
			CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 0));

			// Best Time
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Best Time: %lf(time add in the future)", (popUpWidth / 2.0f), (popUpHeight / 2.0f - 100));

			// Number of Moves
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Number of Moves: %lf(no. of moves)", (popUpWidth / 2.0f), (popUpHeight / 2.0f - 50));

			// -----Play Button-----
			CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
			CP_Graphics_DrawRect((popUpWidth / 2.0f), (popUpHeight / 2.0f + 50), levelButtonWidth, levelButtonHeight);
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText("Play!", (popUpWidth / 2.0f), (popUpHeight / 2.0f + 50));

			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
			{
				// -----Play Input-----
				if (IsAreaClicked((popUpWidth / 2.0f), (popUpHeight / 2.0f + 50), levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
				{
					CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit); // play.c > goes to level select > click level to play
				}
			}

			//CP_Engine_SetNextGameStateForced(levelSelection_Init, levelSelection_Update, level1_exit);
			//CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit); // play.c > goes to level select > click level to play
		}

		// -----Level 2 Input-----
		if (IsAreaClicked((windowWidth / 2.0f + 100), (windowHeight / 2.0f - 100), levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
			//CP_Engine_SetNextGameStateForced(level2_init, level2_update, level2_exit); // play.c > goes to level select > click level to play
		}

		// -----Level 3 Input-----
		if (IsAreaClicked((windowWidth / 2.0f - 100), (windowHeight / 2.0f + 100), levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
			//CP_Engine_SetNextGameStateForced(level3_init, level3_update, level3_exit); // play.c > goes to level select > click level to play
		}

		// -----Level 4 Input-----
		if (IsAreaClicked((windowWidth / 2.0f - 100), (windowHeight / 2.0f + 100), levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_Terminate();
		}
	}


// ---------------------------------------------------------------Main Menu Exit---------------------------------------------------------------
void play_Exit()
{
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
}
