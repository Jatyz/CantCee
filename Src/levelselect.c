#include "cprocessing.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "level7.h"
#include "level8.h"
#include "level9.h"
#include "level10.h"
#include "level11.h"
#include "level12.h"
#include "level13.h"
#include "level14.h"
#include "level15.h"
#include "game.h"
#include "play.h"
#include "levelselect.h"
#include "mainmenu.h"
#include "levelTransition.h"
#include "levelselect.h"
#include "panels.h"
#include "utils.h"

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
	transitLevel();
	CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit);

}

void startLevel2(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level2_init, level2_update, level2_exit);


}

void startLevel3(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level3_init, level3_update, level3_exit);

}

void startLevel4(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level4_init, level4_update, level4_exit);
}

void startLevel5(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level5_init, level5_update, level5_exit);
}


void startLevel6(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level6_init, level6_update, level6_exit);
}

void startLevel7(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level7_init, level7_update, level7_exit);
}

void startLevel8(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level8_init, level8_update, level8_exit);
}

void startLevel9(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level9_init, level9_update, level9_exit);
}

void startLevel10(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level10_init, level10_update, level10_exit);
}

void startLevel11(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level11_init, level11_update, level11_exit);
}

void startLevel12(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level12_init, level12_update, level12_exit);
}

void startLevel13(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level13_init, level13_update, level13_exit);
}

void startLevel14(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level14_init, level14_update, level14_exit);
}

void startLevel15(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level15_init, level15_update, level15_exit);
}

void startGame(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(game_init, game_update, game_exit);
}

void transitLevel(void)
{
	levelExited = 1;

	if (levelExited)	//when level exit, 
	{	//render exit level transition animation
		levelExited = exitLevelTransition(levelExited);	//second parameter runs when the animation is complete, returns 0 when animation is done
		if (!levelExited) {
			levelExited = 0;
		}		
	}
}


void startLevelSelect(void) {
	CP_Engine_SetNextGameStateForced(play_Init, play_Update, play_Exit);
}


void levelSelection_Exit()
{
	
}

