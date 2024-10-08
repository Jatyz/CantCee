//---------------------------------------------------------
// file:	play.c
// author:	Ong You Yang
// email:	youyang.o@digipen.edu
//
// brief:	Level select page
//			
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright � 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include <stdio.h>
#include "utils.h"

#include "mainmenu.h"
#include "play.h"
#include "howToPlay1.h"
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
#include "level9.h"
#include "level10.h"
#include "level11.h"
#include "level12.h"
#include "level13.h"
#include "level14.h"
#include "level15.h"
#include "panels.h"
#include "game.h"

	/*------------------------------------------------------------ Storing Loaded Image in Variable ------------------------------------------------------------*/
CP_Image gradientAccentBackground2 = NULL;
CP_Image selectLevelTitle = NULL;

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

CP_Image hoverLvl = NULL;

CP_Image hoverLvl0Word = NULL;
CP_Image hoverLvl1Word = NULL;
CP_Image hoverLvl2Word = NULL;
CP_Image hoverLvl3Word = NULL;
CP_Image hoverLvl4Word = NULL;

CP_Image hoverLvl5Word = NULL;
CP_Image hoverLvl6Word = NULL;
CP_Image hoverLvl7Word = NULL;
CP_Image hoverLvl8Word = NULL;
CP_Image hoverLvl9Word = NULL;

CP_Image hoverLvl10Word = NULL;
CP_Image hoverLvl11Word = NULL;
CP_Image hoverLvl12Word = NULL;
CP_Image hoverLvl13Word = NULL;
CP_Image hoverLvl14Word = NULL;

CP_Image lsPlayButton = NULL;
CP_Image lsPlayButtonHover = NULL;
CP_Image lsPlayButtonWordHover = NULL;

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
	CP_System_SetWindowSize((int)windowWidth, (int)windowHeight);

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

	/*------------------------------------------------------------ Loading File Path of Image File ------------------------------------------------------------*/
	gradientAccentBackground2 = CP_Image_Load("./Assets/gradientAccentBackground2.png");
	selectLevelTitle = CP_Image_Load("./Assets/selectLevelTitle.png");

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

	hoverLvl = CP_Image_Load("./Assets/hoverLvl.png");

	hoverLvl0Word = CP_Image_Load("./Assets/hoverLvl1Word.png");
	hoverLvl1Word = CP_Image_Load("./Assets/hoverLvl2Word.png");
	hoverLvl2Word = CP_Image_Load("./Assets/hoverLvl3Word.png");
	hoverLvl3Word = CP_Image_Load("./Assets/hoverLvl4Word.png");
	hoverLvl4Word = CP_Image_Load("./Assets/hoverLvl5Word.png");

	hoverLvl5Word = CP_Image_Load("./Assets/hoverLvl6Word.png");
	hoverLvl6Word = CP_Image_Load("./Assets/hoverLvl7Word.png");
	hoverLvl7Word = CP_Image_Load("./Assets/hoverLvl8Word.png");
	hoverLvl8Word = CP_Image_Load("./Assets/hoverLvl9Word.png");
	hoverLvl9Word = CP_Image_Load("./Assets/hoverLvl10Word.png");

	hoverLvl10Word = CP_Image_Load("./Assets/hoverLvl11Word.png");
	hoverLvl11Word = CP_Image_Load("./Assets/hoverLvl12Word.png");
	hoverLvl12Word = CP_Image_Load("./Assets/hoverLvl13Word.png");
	hoverLvl13Word = CP_Image_Load("./Assets/hoverLvl14Word.png");
	hoverLvl14Word = CP_Image_Load("./Assets/hoverLvl15Word.png");

	lsPlayButton = CP_Image_Load("./Assets/lsPlayButton.png");
	lsPlayButtonHover = CP_Image_Load("./Assets/lsPlayButtonHover.png");
	lsPlayButtonWordHover = CP_Image_Load("./Assets/lsPlayButtonWordHover.png");

	buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
}

int once = 0; int levelSelected = 0; int levelScore = 0,parScore = 0;
char test[100];

// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void play_Update()
{
	if (once)
	{
		drawSideBarLevel(test, levelScore);
		drawSideBarPar(parScore);
	}

	// Background: Grey Colour
	CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 0));

	// Set the rectangle drawing mode to CORNER
	CP_Settings_RectMode(CP_POSITION_CORNER);

	// Black selection area 800 x 800
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawRect(0, 0, 800, 800);

	CP_Image_Draw(gradientAccentBackground2, (float)windowWidth / 2, (float)windowHeight / 2, (float)windowWidth, (float)windowHeight, 255);
	CP_Image_Draw(selectLevelTitle, (float)titleX, (float)titleY, (float)CP_Image_GetWidth(selectLevelTitle), (float)CP_Image_GetHeight(selectLevelTitle), 255);

	//if (clicked == 0) {
		// -----Level 1 TO 5-----


	////-----Return To Main Menu Button-----
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Image_Draw(home, (float)firstColumn, (float)exitHeight, (float)CP_Image_GetWidth(home), (float)CP_Image_GetHeight(home), 255);

	//-----Start Button-----
	//CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	//CP_Graphics_DrawRect(fifthColumn, playHeight, levelButtonWidth, levelButtonHeight);
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	//CP_Font_DrawText("Play!", fifthColumn, playHeight);
	CP_Settings_RectMode(CP_POSITION_CORNER);



	//}
		// ------------------------------------------------------------------------------------------ Hover Feature ------------------------------------------------------------------------------------------
	// ------------------------------------------------------------ Level 1 TO 5 Hover ------------------------------------------------------------
	if (IsAreaClicked((float)level[0].xAxis, (float)level[0].yAxis, (float)CP_Image_GetWidth(lvl0), (float)CP_Image_GetHeight(lvl0), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[0].xAxis, (float)level[0].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl0Word, (float)level[0].xAxis, (float)level[0].yAxis, (float)CP_Image_GetWidth(hoverLvl0Word), (float)CP_Image_GetHeight(hoverLvl0Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl0, (float)level[0].xAxis, (float)level[0].yAxis, (float)CP_Image_GetWidth(lvl0), (float)CP_Image_GetHeight(lvl0), 255);
	}
	if (IsAreaClicked((float)level[1].xAxis, (float)level[1].yAxis, (float)CP_Image_GetWidth(lvl1), (float)CP_Image_GetHeight(lvl1), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[1].xAxis, (float)level[1].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl1Word, (float)level[1].xAxis, (float)level[1].yAxis, (float)CP_Image_GetWidth(hoverLvl1Word), (float)CP_Image_GetHeight(hoverLvl1Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl1, (float)level[1].xAxis, (float)level[1].yAxis, (float)CP_Image_GetWidth(lvl1), (float)CP_Image_GetHeight(lvl1), 255);
	}
	if (IsAreaClicked((float)level[2].xAxis, (float)level[2].yAxis, (float)CP_Image_GetWidth(lvl2), (float)CP_Image_GetHeight(lvl2), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[2].xAxis, (float)level[2].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl2Word, (float)level[2].xAxis, (float)level[2].yAxis, (float)CP_Image_GetWidth(hoverLvl2Word), (float)CP_Image_GetHeight(hoverLvl2Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl2, (float)level[2].xAxis, (float)level[2].yAxis, (float)CP_Image_GetWidth(lvl2), (float)CP_Image_GetHeight(lvl2), 255);
	}
	if (IsAreaClicked((float)level[3].xAxis, (float)level[3].yAxis, (float)CP_Image_GetWidth(lvl3), (float)CP_Image_GetHeight(lvl3), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[3].xAxis, (float)level[3].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl3Word, (float)level[3].xAxis, (float)level[3].yAxis, (float)CP_Image_GetWidth(hoverLvl3Word), (float)CP_Image_GetHeight(hoverLvl3Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl3, (float)level[3].xAxis, (float)level[3].yAxis, (float)CP_Image_GetWidth(lvl3), (float)CP_Image_GetHeight(lvl3), 255);
	}
	if (IsAreaClicked((float)level[4].xAxis, (float)level[4].yAxis, (float)CP_Image_GetWidth(lvl4), (float)CP_Image_GetHeight(lvl4), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[4].xAxis, (float)level[4].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl4Word, (float)level[4].xAxis, (float)level[4].yAxis, (float)CP_Image_GetWidth(hoverLvl4Word), (float)CP_Image_GetHeight(hoverLvl4Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl4, (float)level[4].xAxis, (float)level[4].yAxis, (float)CP_Image_GetWidth(lvl4), (float)CP_Image_GetHeight(lvl4), 255);
	}

	// ------------------------------------------------------------ Level 6 TO 10 Hover ------------------------------------------------------------
	if (IsAreaClicked((float)level[5].xAxis, (float)level[5].yAxis, (float)CP_Image_GetWidth(lvl5), (float)CP_Image_GetHeight(lvl5), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[5].xAxis, (float)level[5].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl5Word, (float)level[5].xAxis, (float)level[5].yAxis, (float)CP_Image_GetWidth(hoverLvl5Word), (float)CP_Image_GetHeight(hoverLvl5Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl5, (float)level[5].xAxis, (float)level[5].yAxis, (float)CP_Image_GetWidth(lvl5), (float)CP_Image_GetHeight(lvl5), 255);
	}
	if (IsAreaClicked((float)level[6].xAxis, (float)level[6].yAxis, (float)CP_Image_GetWidth(lvl6), (float)CP_Image_GetHeight(lvl6), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[6].xAxis, (float)level[6].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl6Word, (float)level[6].xAxis, (float)level[6].yAxis, (float)CP_Image_GetWidth(hoverLvl6Word), (float)CP_Image_GetHeight(hoverLvl6Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl6, (float)level[6].xAxis, (float)level[6].yAxis, (float)CP_Image_GetWidth(lvl6), (float)CP_Image_GetHeight(lvl6), 255);
	}
	if (IsAreaClicked((float)level[7].xAxis, (float)level[7].yAxis, (float)CP_Image_GetWidth(lvl7), (float)CP_Image_GetHeight(lvl7), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[7].xAxis, (float)level[7].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl7Word, (float)level[7].xAxis, (float)level[7].yAxis, (float)CP_Image_GetWidth(hoverLvl7Word), (float)CP_Image_GetHeight(hoverLvl7Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl7, (float)level[7].xAxis, (float)level[7].yAxis, (float)CP_Image_GetWidth(lvl7), (float)CP_Image_GetHeight(lvl7), 255);
	}
	if (IsAreaClicked((float)level[8].xAxis, (float)level[8].yAxis, (float)CP_Image_GetWidth(lvl8), (float)CP_Image_GetHeight(lvl8), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[8].xAxis, (float)level[8].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl8Word, (float)level[8].xAxis, (float)level[8].yAxis, (float)CP_Image_GetWidth(hoverLvl8Word), (float)CP_Image_GetHeight(hoverLvl8Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl8, (float)level[8].xAxis, (float)level[8].yAxis, (float)CP_Image_GetWidth(lvl8), (float)CP_Image_GetHeight(lvl8), 255);
	}
	if (IsAreaClicked((float)level[9].xAxis, (float)level[9].yAxis, (float)CP_Image_GetWidth(lvl9), (float)CP_Image_GetHeight(lvl9), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[9].xAxis, (float)level[9].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl9Word, (float)level[9].xAxis, (float)level[9].yAxis, (float)CP_Image_GetWidth(hoverLvl9Word), (float)CP_Image_GetHeight(hoverLvl9Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl9, (float)level[9].xAxis, (float)level[9].yAxis, (float)CP_Image_GetWidth(lvl9), (float)CP_Image_GetHeight(lvl9), 255);
	}

	// ------------------------------------------------------------ Level 11 TO 15 Hover ------------------------------------------------------------
	if (IsAreaClicked((float)level[10].xAxis, (float)level[10].yAxis, (float)CP_Image_GetWidth(lvl10), (float)CP_Image_GetHeight(lvl10), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[10].xAxis, (float)level[10].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl10Word, (float)level[10].xAxis, (float)level[10].yAxis, (float)CP_Image_GetWidth(hoverLvl10Word), (float)CP_Image_GetHeight(hoverLvl10Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl10, (float)level[10].xAxis, (float)level[10].yAxis, (float)CP_Image_GetWidth(lvl10), (float)CP_Image_GetHeight(lvl10), 255);
	}
	if (IsAreaClicked((float)level[11].xAxis, (float)level[11].yAxis, (float)CP_Image_GetWidth(lvl11), (float)CP_Image_GetHeight(lvl11), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[11].xAxis, (float)level[11].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl11Word, (float)level[11].xAxis, (float)level[11].yAxis, (float)CP_Image_GetWidth(hoverLvl11Word), (float)CP_Image_GetHeight(hoverLvl11Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl11, (float)level[11].xAxis, (float)level[11].yAxis, (float)CP_Image_GetWidth(lvl11), (float)CP_Image_GetHeight(lvl11), 255);
	}
	if (IsAreaClicked((float)level[12].xAxis, (float)level[12].yAxis, (float)CP_Image_GetWidth(lvl12), (float)CP_Image_GetHeight(lvl12), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[12].xAxis, (float)level[12].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl12Word, (float)level[12].xAxis, (float)level[12].yAxis, (float)CP_Image_GetWidth(hoverLvl12Word), (float)CP_Image_GetHeight(hoverLvl12Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl12, (float)level[12].xAxis, (float)level[12].yAxis, (float)CP_Image_GetWidth(lvl12), (float)CP_Image_GetHeight(lvl12), 255);
	}
	if (IsAreaClicked((float)level[13].xAxis, (float)level[13].yAxis, (float)CP_Image_GetWidth(lvl13), (float)CP_Image_GetHeight(lvl13), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[13].xAxis, (float)level[13].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl13Word, (float)level[13].xAxis, (float)level[13].yAxis, (float)CP_Image_GetWidth(hoverLvl13Word), (float)CP_Image_GetHeight(hoverLvl13Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl13, (float)level[13].xAxis, (float)level[13].yAxis, (float)CP_Image_GetWidth(lvl13), (float)CP_Image_GetHeight(lvl13), 255);
	}
	if (IsAreaClicked((float)level[14].xAxis, (float)level[14].yAxis, (float)CP_Image_GetWidth(lvl14), (float)CP_Image_GetHeight(lvl14), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(hoverLvl, (float)level[14].xAxis, (float)level[14].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		CP_Image_Draw(hoverLvl14Word, (float)level[14].xAxis, (float)level[14].yAxis, (float)CP_Image_GetWidth(hoverLvl14Word), (float)CP_Image_GetHeight(hoverLvl14Word), 255);
	}
	else
	{
		CP_Image_Draw(lvl14, (float)level[14].xAxis, (float)level[14].yAxis, (float)CP_Image_GetWidth(lvl14), (float)CP_Image_GetHeight(lvl14), 255);
	}

	if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
	{
		CP_Image_Draw(lsPlayButtonHover, fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButtonHover), (float)CP_Image_GetHeight(lsPlayButtonHover), 255);
		CP_Image_Draw(lsPlayButtonWordHover, fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButtonWordHover), (float)CP_Image_GetHeight(lsPlayButtonWordHover), 255);
	}
	else
	{
		CP_Image_Draw(lsPlayButton, fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), 255);
	}
	


	// ---------------------------------------------------------------------- LEVEL SELECTION ----------------------------------------------------------------------
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		// ---------------------------------------------------------------------- Level 1 TO 5 ----------------------------------------------------------------------
		if (IsAreaClicked((float)level[0].xAxis, (float)level[0].yAxis, (float)CP_Image_GetWidth(lvl0), (float)CP_Image_GetHeight(lvl0), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[0].selected = 1;
			parScore = 10;
			levelScore = Score[1];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 1");
		}
		if (IsAreaClicked((float)level[1].xAxis, (float)level[1].yAxis, (float)CP_Image_GetWidth(lvl1), (float)CP_Image_GetHeight(lvl1), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[1].selected = 1;

			levelScore = Score[2];
			parScore = 22;
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 2");
		}
		if (IsAreaClicked((float)level[2].xAxis, (float)level[2].yAxis, (float)CP_Image_GetWidth(lvl2), (float)CP_Image_GetHeight(lvl2), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[2].selected = 1;
			parScore = 17;
			levelScore = Score[3];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 3");
		}
		if (IsAreaClicked((float)level[3].xAxis, (float)level[3].yAxis, (float)CP_Image_GetWidth(lvl3), (float)CP_Image_GetHeight(lvl3), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[3].selected = 1;
			parScore = 36;
			levelScore = Score[4];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 4");
		}
		if (IsAreaClicked((float)level[4].xAxis, (float)level[4].yAxis, (float)CP_Image_GetWidth(lvl4), (float)CP_Image_GetHeight(lvl4), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[4].selected = 1;
			parScore = 109;
			levelScore = Score[5];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 5");
		}

		// ---------------------------------------------------------------------- LEVEL 6 TO 10 ----------------------------------------------------------------------
		if (IsAreaClicked((float)level[5].xAxis, (float)level[5].yAxis, (float)CP_Image_GetWidth(lvl5), (float)CP_Image_GetHeight(lvl5), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[5].selected = 1;
			parScore = 12;
			levelScore = Score[6];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 6");
		}
		if (IsAreaClicked((float)level[6].xAxis, (float)level[6].yAxis, (float)CP_Image_GetWidth(lvl6), (float)CP_Image_GetHeight(lvl6), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[6].selected = 1;
			parScore = 18;
			levelScore = Score[7];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 7");
		}
		if (IsAreaClicked((float)level[7].xAxis, (float)level[7].yAxis, (float)CP_Image_GetWidth(lvl7), (float)CP_Image_GetHeight(lvl7), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[7].selected = 1;
			parScore = 118;
			levelScore = Score[8];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 8");
		}
		if (IsAreaClicked((float)level[8].xAxis, (float)level[8].yAxis, (float)CP_Image_GetWidth(lvl8), (float)CP_Image_GetHeight(lvl8), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[8].selected = 1;
			parScore = 45;
			levelScore = Score[9];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 9");
		}
		if (IsAreaClicked((float)level[9].xAxis, (float)level[9].yAxis, (float)CP_Image_GetWidth(lvl9), (float)CP_Image_GetHeight(lvl9), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[9].selected = 1;
			parScore = 118;
			levelScore = Score[10];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 10");
		}

		// ----------------------------------------------------------------------LEVEL 11 TO 15 ----------------------------------------------------------------------
		if (IsAreaClicked((float)level[10].xAxis, (float)level[10].yAxis, (float)CP_Image_GetWidth(lvl10), (float)CP_Image_GetHeight(lvl10), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[10].selected = 1;
			parScore = 136;
			levelScore = Score[11];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 11");
		}
		if (IsAreaClicked((float)level[11].xAxis, (float)level[11].yAxis, (float)CP_Image_GetWidth(lvl11), (float)CP_Image_GetHeight(lvl11), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[11].selected = 1;
			parScore = 137;
			levelScore = Score[12];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 12");
		}
		if (IsAreaClicked((float)level[12].xAxis, (float)level[12].yAxis, (float)CP_Image_GetWidth(lvl12), (float)CP_Image_GetHeight(lvl12), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[12].selected = 1;
			parScore = 140;
			levelScore = Score[13];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 13");
		}
		if (IsAreaClicked((float)level[13].xAxis, (float)level[13].yAxis, (float)CP_Image_GetWidth(lvl13), (float)CP_Image_GetHeight(lvl13), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[13].selected = 1;
			parScore = 218;
			levelScore = Score[14];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 14");
		}
		if (IsAreaClicked((float)level[14].xAxis, (float)level[14].yAxis, (float)CP_Image_GetWidth(lvl14), (float)CP_Image_GetHeight(lvl14), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
			{
				level[setLevelSelectionState].selected = 0;
			}
			level[14].selected = 1;
			parScore = 143;
			levelScore = Score[15];
			once = 1;
			levelSelected = 1;
			sprintf_s(test, 100, "Level 15");
		}

		// Back to main menu
		if (IsAreaClicked((float)firstColumn, (float)exitHeight, (float)CP_Image_GetWidth(home), (float)CP_Image_GetHeight(home), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
		}
	}


	// ---------------------------------------------------------------------- Start Level[X] ----------------------------------------------------------------------
	// if Level [X] is selected, & PLAY is clicked > enter game
	// ----------------------------------------------------------------------Level 1 TO 5----------------------------------------------------------------------
	if (level[0].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit);
		}
	}
	if (level[1].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level2_init, level2_update, level2_exit);
		}
	}
	if (level[2].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level3_init, level3_update, level3_exit);
		}
	}
	if (level[3].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level4_init, level4_update, level4_exit);
		}
	}
	if (level[4].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level5_init, level5_update, level5_exit);
		}
	}

	// ----------------------------------------------------------------------Level 6 TO 10----------------------------------------------------------------------
	if (level[5].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level6_init, level6_update, level6_exit);
		}
	}
	if (level[6].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level7_init, level7_update, level7_exit);
		}
	}
	if (level[7].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level8_init, level8_update, level8_exit);
		}
	}
	if (level[8].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level9_init, level9_update, level9_exit);
		}
	}
	if (level[9].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level10_init, level10_update, level10_exit);
		}
	}

	// ----------------------------------------------------------------------Level 11 TO 15----------------------------------------------------------------------
	if (level[10].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level11_init, level11_update, level11_exit);
		}
	}
	if (level[11].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level12_init, level12_update, level12_exit);
		}
	}
	if (level[12].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level13_init, level13_update, level13_exit);
		}
	}
	if (level[13].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level14_init, level14_update, level14_exit);
		}
	}
	if (level[14].selected == 1 && CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		if (IsAreaClicked(fifthColumn, playHeight, (float)CP_Image_GetWidth(lsPlayButton), (float)CP_Image_GetHeight(lsPlayButton), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
			CP_Engine_SetNextGameStateForced(level15_init, level15_update, level15_exit);
		}
	}

	for (int setLevelSelectionState = 0; setLevelSelectionState < 15; setLevelSelectionState++)
	{
		if (level[setLevelSelectionState].selected)
		{
			CP_Image_Draw(hoverLvl, (float)level[setLevelSelectionState].xAxis, (float)level[setLevelSelectionState].yAxis, (float)CP_Image_GetWidth(hoverLvl), (float)CP_Image_GetHeight(hoverLvl), 255);
		}
	}
}

	/*------------------------------------------------------------ Freeing of Images ------------------------------------------------------------*/
void play_Exit()
{
	CP_Image_Free(&gradientAccentBackground2);
	CP_Image_Free(&selectLevelTitle);

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

	CP_Image_Free(&home);
	CP_Image_Free(&hoverLvl);

	CP_Image_Free(&hoverLvl0Word);
	CP_Image_Free(&hoverLvl1Word);
	CP_Image_Free(&hoverLvl2Word);
	CP_Image_Free(&hoverLvl3Word);
	CP_Image_Free(&hoverLvl4Word);

	CP_Image_Free(&hoverLvl5Word);
	CP_Image_Free(&hoverLvl6Word);
	CP_Image_Free(&hoverLvl7Word);
	CP_Image_Free(&hoverLvl8Word);
	CP_Image_Free(&hoverLvl9Word);

	CP_Image_Free(&hoverLvl10Word);
	CP_Image_Free(&hoverLvl11Word);
	CP_Image_Free(&hoverLvl12Word);
	CP_Image_Free(&hoverLvl13Word);
	CP_Image_Free(&hoverLvl14Word);
	
	CP_Image_Free(&lsPlayButton);
	CP_Image_Free(&lsPlayButtonHover);
	CP_Image_Free(&lsPlayButtonWordHover);

	CP_Sound_Free(&buttonSound);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_LEFT, CP_TEXT_ALIGN_V_BASELINE);
}
