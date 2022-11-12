#include "cprocessing.h"
#include "utils.h"
#include <stdio.h>
#include "mainmenu.h"
#include "play.h"
#include "howToPlay.h"
#include "settings.h"
#include "levelselect.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "level7.h"
#include "level8.h"
#include "panels.h"
#include "game.h"

CP_Image gradientAccentBackground2 = NULL;

CP_Image lvl0 = NULL;
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
CP_Image lvl13 = NULL;
CP_Image lvl14 = NULL;

CP_Image home = NULL;

typedef struct Level
{
	double xAxis;
	double yAxis;
	int selected;
} Level;
Level level[15];

void play_Init()
{
	// Set the window size to a sqaure 1000 x 800
	CP_System_SetWindowSize(windowWidth, windowHeight);

	// All Text size
	CP_Settings_TextSize(20.0f);

	// All Text allignment
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	// Level 1 TO 5
	level[0].xAxis = firstColumn;
	level[0].yAxis = firstRowHeight;
	level[0].selected = 0;

	level[1].xAxis = secondColumn;
	level[1].yAxis = firstRowHeight;
	level[1].selected = 0;

	level[2].xAxis = thirdColumn;
	level[2].yAxis = firstRowHeight;
	level[2].selected = 0;

	level[3].xAxis = fourthColumn;
	level[3].yAxis = firstRowHeight;
	level[3].selected = 0;

	level[4].xAxis = fifthColumn;
	level[4].yAxis = firstRowHeight;
	level[4].selected = 0;

	// Level 6 TO 10
	level[5].xAxis = firstColumn;
	level[5].yAxis = secondRowHeight;
	level[5].selected = 0;

	level[6].xAxis = secondColumn;
	level[6].yAxis = secondRowHeight;
	level[6].selected = 0;

	level[7].xAxis = thirdColumn;
	level[7].yAxis = secondRowHeight;
	level[7].selected = 0;

	level[8].xAxis = fourthColumn;
	level[8].yAxis = secondRowHeight;
	level[8].selected = 0;

	level[9].xAxis = fifthColumn;
	level[9].yAxis = secondRowHeight;
	level[9].selected = 0;

	// Level 11 TO 15
	level[10].xAxis = firstColumn;
	level[10].yAxis = thirdRowHeight;
	level[10].selected = 0;

	level[11].xAxis = secondColumn;
	level[11].yAxis = thirdRowHeight;
	level[11].selected = 0;

	level[12].xAxis = thirdColumn;
	level[12].yAxis = thirdRowHeight;
	level[12].selected = 0;

	level[13].xAxis = fourthColumn;
	level[13].yAxis = thirdRowHeight;
	level[13].selected = 0;

	level[14].xAxis = fifthColumn;
	level[14].yAxis = thirdRowHeight;
	level[14].selected = 0;

	gradientAccentBackground2 = CP_Image_Load("./Assets/gradientAccentBackground2.png");

	lvl0 = CP_Image_Load("./Assets/lvl1.png");
	lvl1 = CP_Image_Load("./Assets/lvl2.png");
	lvl2 = CP_Image_Load("./Assets/lvl3.png");
	lvl3 = CP_Image_Load("./Assets/lvl4.png");
	lvl4 = CP_Image_Load("./Assets/lvl5.png");

	lvl5 = CP_Image_Load("./Assets/lvl6.png");
	lvl6 = CP_Image_Load("./Assets/lvl7.png");
	lvl7 = CP_Image_Load("./Assets/lvl8.png");
	lvl8 = CP_Image_Load("./Assets/lvl9.png");
	lvl9 = CP_Image_Load("./Assets/lvl10.png");

	lvl10 = CP_Image_Load("./Assets/lvl11.png");
	lvl11 = CP_Image_Load("./Assets/lvl12.png");
	lvl12 = CP_Image_Load("./Assets/lvl13.png");
	lvl13 = CP_Image_Load("./Assets/lvl14.png");
	lvl14 = CP_Image_Load("./Assets/lvl15.png");

	home = CP_Image_Load("./Assets/home.png");
}

int once = 0; int levelSelected = 0;
char test[100];
// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void play_Update()
{
	if (once)
	{
		drawSideBar(test, Score[1]);
	}

	// Background: Grey Colour
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 0));

	// Set the rectangle drawing mode to CORNER
	CP_Settings_RectMode(CP_POSITION_CORNER);

	// Black selection area 800 x 800
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(0, 0, 800, 800);

	CP_Image_Draw(gradientAccentBackground2, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);


	//if (clicked == 0) {
		// -----Level 1 TO 5-----
	CP_Image_Draw(lvl0, level[0].xAxis, level[0].yAxis, CP_Image_GetWidth(lvl0), CP_Image_GetHeight(lvl0), 255);
	CP_Image_Draw(lvl1, level[1].xAxis, level[1].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), 255);
	CP_Image_Draw(lvl2, level[2].xAxis, level[2].yAxis, CP_Image_GetWidth(lvl2), CP_Image_GetHeight(lvl2), 255);
	CP_Image_Draw(lvl3, level[3].xAxis, level[3].yAxis, CP_Image_GetWidth(lvl3), CP_Image_GetHeight(lvl3), 255);
	CP_Image_Draw(lvl4, level[4].xAxis, level[4].yAxis, CP_Image_GetWidth(lvl4), CP_Image_GetHeight(lvl4), 255);

	CP_Image_Draw(lvl5, level[5].xAxis, level[5].yAxis, CP_Image_GetWidth(lvl5), CP_Image_GetHeight(lvl5), 255);
	CP_Image_Draw(lvl6, level[6].xAxis, level[6].yAxis, CP_Image_GetWidth(lvl6), CP_Image_GetHeight(lvl6), 255);
	CP_Image_Draw(lvl7, level[7].xAxis, level[7].yAxis, CP_Image_GetWidth(lvl7), CP_Image_GetHeight(lvl7), 255);
	CP_Image_Draw(lvl8, level[8].xAxis, level[8].yAxis, CP_Image_GetWidth(lvl8), CP_Image_GetHeight(lvl8), 255);
	CP_Image_Draw(lvl9, level[9].xAxis, level[9].yAxis, CP_Image_GetWidth(lvl9), CP_Image_GetHeight(lvl9), 255);

	CP_Image_Draw(lvl10, level[10].xAxis, level[10].yAxis, CP_Image_GetWidth(lvl10), CP_Image_GetHeight(lvl10), 255);
	CP_Image_Draw(lvl11, level[11].xAxis, level[11].yAxis, CP_Image_GetWidth(lvl11), CP_Image_GetHeight(lvl11), 255);
	CP_Image_Draw(lvl12, level[12].xAxis, level[12].yAxis, CP_Image_GetWidth(lvl12), CP_Image_GetHeight(lvl12), 255);
	CP_Image_Draw(lvl13, level[13].xAxis, level[13].yAxis, CP_Image_GetWidth(lvl13), CP_Image_GetHeight(lvl13), 255);
	CP_Image_Draw(lvl14, level[14].xAxis, level[14].yAxis, CP_Image_GetWidth(lvl14), CP_Image_GetHeight(lvl14), 255);

	////-----Return To Main Menu Button-----
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Image_Draw(home, firstColumn, exitHeight, CP_Image_GetWidth(home), CP_Image_GetHeight(home), 255);

	//-----Exit Button-----
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawRect(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("Play!", fifthColumn, playHeight);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	//}

	// Selection of Level
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		// ----------Level 1 TO 5----------
		if (IsAreaClicked(level[0].xAxis, level[0].yAxis, CP_Image_GetWidth(lvl0), CP_Image_GetHeight(lvl0), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[0].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 1");
		}
		if (IsAreaClicked(level[1].xAxis, level[1].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[1].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 2");
		}
		if (IsAreaClicked(level[2].xAxis, level[2].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[2].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 3");
		}
		if (IsAreaClicked(level[3].xAxis, level[3].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[3].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 4");
		}
		if (IsAreaClicked(level[4].xAxis, level[4].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[4].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 5");
		}

		// ---------- 6 TO 10----------
		if (IsAreaClicked(level[5].xAxis, level[5].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[5].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 6");
		}
		if (IsAreaClicked(level[6].xAxis, level[6].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[6].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 7");
		}
		if (IsAreaClicked(level[7].xAxis, level[7].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[7].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 8");
		}
		if (IsAreaClicked(level[8].xAxis, level[8].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[8].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 9");
		}
		if (IsAreaClicked(level[9].xAxis, level[9].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[9].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 10");
		}

		// ----------Level 11 TO 15----------
		if (IsAreaClicked(level[10].xAxis, level[10].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[10].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 11");
		}
		if (IsAreaClicked(level[11].xAxis, level[11].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[11].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 12");
		}
		if (IsAreaClicked(level[12].xAxis, level[12].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[12].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 13");
		}
		if (IsAreaClicked(level[13].xAxis, level[13].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[13].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 14");
		}
		if (IsAreaClicked(level[14].xAxis, level[14].yAxis, CP_Image_GetWidth(lvl1), CP_Image_GetHeight(lvl1), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			level[14].selected = 1;
			once = 1;
			levelSelected = 1;
			sprintf_s(&test, 100, "Level 15");
		}
	}

	// if Level [X] is selected, & Start is clicked > enter game
	// ----------Level 1 TO 5----------
	if (level[0].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit);
		}
	}
	if (level[1].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level2_init, level2_update, level2_exit);
		}
	}
	if (level[2].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level3_init, level3_update, level3_exit);
		}
	}
	if (level[3].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level4_init, level4_update, level4_exit);
		}
	}
	if (level[4].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level5_init, level5_update, level5_exit);
		}
	}

	// ----------Level 6 TO 10----------
	if (level[5].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level6_init, level6_update, level6_exit);
		}
	}
	if (level[6].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level7_init, level7_update, level7_exit);
		}
	}
	if (level[7].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(level8_init, level8_update, level8_exit);
		}
	}
	//if (level[8].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	//{
	//	if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	//	{
	//		CP_Engine_SetNextGameStateForced(level9_init, level9_update, level9_exit);
	//	}
	//}
	//if (level[9].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	//{
	//	if (IsAreaClicked(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
	//	{
	//		CP_Engine_SetNextGameStateForced(level10_init, level10_update, level10_exit);
	//	}
	//}


		// Back to main menu
		if (IsAreaClicked(firstColumn, exitHeight, CP_Image_GetWidth(home), CP_Image_GetHeight(home), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
		}

	}





// ---------------------------------------------------------------Main Menu Exit---------------------------------------------------------------
void play_Exit()
{
	CP_Image_Free(&gradientAccentBackground2);

	CP_Image_Free(&lvl0);
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

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
}
