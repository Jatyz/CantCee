#include "cprocessing.h"
#include "utils.h"

#include "mainmenu.h"
#include "play.h"
#include "howToPlay.h"
#include "settings.h"
#include "levelselect.h"
#include "level1.h"

CP_Image lvl1 = NULL;
CP_Image lvl2 = NULL;
CP_Image lvl3 = NULL;
CP_Image lvl4 = NULL;
CP_Image lvl5 = NULL;

CP_Image lvl6 = NULL;
CP_Image lvl7 = NULL;
CP_Image lvl8 = NULL;
CP_Image lvl9 = NULL;
CP_Image lvl10 = NULL;

CP_Image lvl11 = NULL;
CP_Image lvl12 = NULL;
CP_Image lvl13= NULL;
CP_Image lvl14 = NULL;
CP_Image lvl15 = NULL;

int clicked = 0;

void play_Init()
{
	// Set the window size to a sqaure 1000 x 800
	CP_System_SetWindowSize(windowWidth, windowHeight);


	// All Text size
	CP_Settings_TextSize(20.0f);

	// All Text allignment
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	lvl1 = CP_Image_Load("./Assets/lvl1.png");
	lvl2 = CP_Image_Load("./Assets/lvl2.png");
	lvl3 = CP_Image_Load("./Assets/lvl3.png");
	lvl4 = CP_Image_Load("./Assets/lvl4.png");
	lvl5 = CP_Image_Load("./Assets/lvl5.png");

	lvl6 = CP_Image_Load("./Assets/lvl6.png");
	lvl7 = CP_Image_Load("./Assets/lvl7.png");
	lvl8 = CP_Image_Load("./Assets/lvl8.png");
	lvl9 = CP_Image_Load("./Assets/lvl9.png");
	lvl10 = CP_Image_Load("./Assets/lvl10.png");

	lvl11 = CP_Image_Load("./Assets/lvl11.png");
	lvl12 = CP_Image_Load("./Assets/lvl12.png");
	lvl13 = CP_Image_Load("./Assets/lvl13.png");
	lvl14 = CP_Image_Load("./Assets/lvl14.png");
	lvl15 = CP_Image_Load("./Assets/lvl15.png");

}


// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void play_Update()
{
	// Background: Grey Colour
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

	// Set the rectangle drawing mode to CORNER
	CP_Settings_RectMode(CP_POSITION_CORNER);

	//
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(0, 0, 800, 800);

	if (clicked == 0) {
		// -----Level 1 TO 5-----
		CP_Image_Draw(lvl1, firstColumn, firstRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl2, secondColumn, firstRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl3, thirdColumn, firstRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl4, fourthColumn, firstRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl5, fifthColumn, firstRowHeight, levelButtonWidth, levelButtonHeight, 255);

		CP_Image_Draw(lvl6, firstColumn, secondRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl7, secondColumn, secondRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl8, thirdColumn, secondRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl9, fourthColumn, secondRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl10, fifthColumn, secondRowHeight, levelButtonWidth, levelButtonHeight, 255);

		CP_Image_Draw(lvl11, firstColumn, thirdRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl12, secondColumn, thirdRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl13, thirdColumn, thirdRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl14, fourthColumn, thirdRowHeight, levelButtonWidth, levelButtonHeight, 255);
		CP_Image_Draw(lvl15, fifthColumn, thirdRowHeight, levelButtonWidth, levelButtonHeight, 255);

	}



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
	CP_Image_Free(&lvl1);
	CP_Image_Free(&lvl2);
	CP_Image_Free(&lvl3);
	CP_Image_Free(&lvl4);
	CP_Image_Free(&lvl5);

	CP_Image_Free(&lvl6);
	CP_Image_Free(&lvl7);
	CP_Image_Free(&lvl8);
	CP_Image_Free(&lvl9);
	CP_Image_Free(&lvl10);

	CP_Image_Free(&lvl11);
	CP_Image_Free(&lvl12);
	CP_Image_Free(&lvl13);
	CP_Image_Free(&lvl14);
	CP_Image_Free(&lvl15);


	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
}
