#include "cprocessing.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "game.h"
#include "play.h"
#include "mainmenu.h"


//need a method to run level select as well
void levelSelection_Init()
{
	// Set the window size to a sqaure 400 x 400
	CP_System_SetWindowSize(popUpWidth, popUpHeight);

	// Set the rectangle drawing mode to CENTER
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// All Text size
	CP_Settings_TextSize(20.0f);

	// All Text allignment
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void levelSelection_Update()
{
	// Background: Grey Colour
	CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 0));
	
	// Best Time
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Best Time: %lf(time add in the future)", (popUpWidth / 2.0f), (popUpHeight / 2.0f - 100));

	// Number of moves
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
		if (IsAreaClicked((windowWidth / 2.0f), (windowHeight / 2.0f + 50), levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit); // play.c > goes to level select > click level to play
		}
	}
}

void startLevel1(void)
{
	CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit);
}

void startLevel2(void)
{
	CP_Engine_SetNextGameStateForced(level2_init, level2_update, level2_exit);
}

void startLevel3(void)
{
	CP_Engine_SetNextGameStateForced(level3_init, level3_update, level3_exit);
}

void startGame(void)
{
	CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
}

void startLevelSelect(void) {

	CP_Engine_SetNextGameStateForced(play_Init, play_Update, play_Exit);
}

void levelSelection_Exit()
{
	
}
