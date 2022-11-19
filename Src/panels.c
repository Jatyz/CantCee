#include "cprocessing.h"
#include "grid.h"
#include "game.h"
#include "player.h"
#include "utils.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdlib.h>
#include "panels.h"

CP_Image pauseBackground = NULL;

CP_Image pMenuHover = NULL;

// Pause Menu
CP_Image pauseMenuBackground = NULL;
CP_Image pauseMenuTitle = NULL;

CP_Image pMenuSelectLevelWord = NULL;
CP_Image pMenuRestartWord = NULL;
CP_Image pMenuReturnToGame = NULL;

CP_Image pMenuSelectLevelWordHover = NULL;
CP_Image pMenuRestartWordHover = NULL;
CP_Image pMenuReturnToGameHover = NULL;

// Lose Menu
//CP_Image loseMenuBackground = NULL;
CP_Image loseMenuTitle = NULL;

CP_Image lMenuRestartWord = NULL;
CP_Image lMenuSelectLevel = NULL;

CP_Image lMenuRestartWordHover = NULL;
CP_Image lMenuSelectLevelHover = NULL;

// Victory Menu
CP_Image victoryMenuTitle = NULL;

CP_Image vNextLvlWord = NULL;
CP_Image vMenuRestartWord = NULL;
CP_Image vMenuSelectLevelWord = NULL;

CP_Image vNextLvlWordHover = NULL;
CP_Image vMenuRestartWordHover = NULL;
CP_Image vMenuSelectLevelWordHover = NULL;

CP_Image pauseGradient = NULL;

//draws a full button that covers the screen,and there is a small panel with buttons depending on the state the button that shows up are different and does different things.
void drawFullPanel(void) {

	CP_Settings_NoStroke();
	//CP_Settings_Fill(CP_Color_Create(0, 0, 0, 122));
	//CP_Graphics_DrawRect(0, 0, 800, 800);

	float smallpanelx = 500, smallpanely = 400;

	float panelStartx = 400 - smallpanelx / 2;
	float panelStarty = 400 - smallpanely / 2;

	//CP_Settings_Fill(CP_Color_Create(122, 122, 122, 255));
	//CP_Graphics_DrawRect(panelStartx, panelStarty, smallpanelx, smallpanely);

	pauseBackground = CP_Image_Load("./Assets/pauseBackground.png");
	//pauseGradient = CP_Image_Load("./Assets/pauseGradient.png");
	pMenuHover = CP_Image_Load("./Assets/pMenuHover.png");

	// Pause Menu
	pauseMenuBackground = CP_Image_Load("./Assets/pauseMenuBackground.png");
	pauseMenuTitle = CP_Image_Load("./Assets/pauseMenuTitle.png");

	pMenuSelectLevelWord = CP_Image_Load("./Assets/pMenuSelectLevelWord.png");
	pMenuRestartWord = CP_Image_Load("./Assets/pMenuRestartWord.png");
	pMenuReturnToGame = CP_Image_Load("./Assets/pMenuReturnToGame.png");

	pMenuSelectLevelWordHover = CP_Image_Load("./Assets/pMenuSelectLevelWordHover.png");
	pMenuRestartWordHover = CP_Image_Load("./Assets/pMenuRestartWordHover.png");
	pMenuReturnToGameHover = CP_Image_Load("./Assets/pMenuReturnToGameHover.png");

	// Lose Menu
	//loseMenuBackground = CP_Image_Load("./Assets/loseMenuBackground.png");
	loseMenuTitle = CP_Image_Load("./Assets/loseMenuTitle.png");

	lMenuRestartWord = CP_Image_Load("./Assets/lMenuRestartWord.png");
	lMenuSelectLevel = CP_Image_Load("./Assets/lMenuSelectLevel.png");

	lMenuRestartWordHover = CP_Image_Load("./Assets/lMenuRestartWordHover.png");
	lMenuSelectLevelHover = CP_Image_Load("./Assets/lMenuSelectLevelHover.png");

	// Victory Menu
	victoryMenuTitle = CP_Image_Load("./Assets/victoryMenuTitle.png");

	vNextLvlWord = CP_Image_Load("./Assets/vNextLvlWord.png");
	vMenuRestartWord = CP_Image_Load("./Assets/vMenuRestartWord.png");
	vMenuSelectLevelWord = CP_Image_Load("./Assets/vMenuSelectLevelWord.png");

	vNextLvlWordHover = CP_Image_Load("./Assets/vNextLvlWordHover.png");
	vMenuRestartWordHover = CP_Image_Load("./Assets/vMenuRestartWordHover.png");
	vMenuSelectLevelWordHover = CP_Image_Load("./Assets/vMenuSelectLevelWordHover.png");

	CP_Image_Draw(pauseBackground, gameCenterX, gameCenterY, gameWindowWidth, gameWindowHeight, 255);

	//for the button add switch case depending on what is the current game state
	//add a game state under game.h
	// 
	//CP_Settings_ImageMode(CP_POSITION_CENTER);


	CP_Settings_RectMode(CP_POSITION_CENTER);
	switch (gameState) {
	case PAUSED:
		CP_Image_Draw(pauseMenuBackground, gameCenterX, gameCenterY, CP_Image_GetWidth(pauseMenuBackground), CP_Image_GetHeight(pauseMenuBackground), 255);
		CP_Image_Draw(pauseMenuTitle, gameCenterX, pauseMenuY, CP_Image_GetWidth(pauseMenuTitle), CP_Image_GetHeight(pauseMenuTitle), 255);

		// Pause Menu Select Level
		if (IsAreaClicked(gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(pMenuSelectLevelWord), CP_Image_GetHeight(pMenuSelectLevelWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(pMenuSelectLevelWordHover, gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(pMenuSelectLevelWordHover), CP_Image_GetHeight(pMenuSelectLevelWordHover), 255);
		}
		else
		{
			CP_Image_Draw(pMenuSelectLevelWord, gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(pMenuSelectLevelWord), CP_Image_GetHeight(pMenuSelectLevelWord), 255);
		}
		
		// Pause Menu Restart
		if (IsAreaClicked(gameCenterX, pMenuRestartY, CP_Image_GetWidth(pMenuSelectLevelWord), CP_Image_GetHeight(pMenuSelectLevelWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuRestartY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(pMenuRestartWordHover, gameCenterX, pMenuRestartY, CP_Image_GetWidth(pMenuRestartWordHover), CP_Image_GetHeight(pMenuRestartWordHover), 255);
		}
		else
		{
			CP_Image_Draw(pMenuRestartWord, gameCenterX, pMenuRestartY, CP_Image_GetWidth(pMenuRestartWord), CP_Image_GetHeight(pMenuRestartWord), 255);
		}

		// Pause Menu Return To Game
		if (IsAreaClicked(gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(pMenuReturnToGame), CP_Image_GetHeight(pMenuReturnToGame), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(pMenuReturnToGameHover, gameCenterX, pMenuRtoGameY + 5 , CP_Image_GetWidth(pMenuReturnToGameHover), CP_Image_GetHeight(pMenuReturnToGameHover), 255);
		}
		else
		{
			CP_Image_Draw(pMenuReturnToGame, gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(pMenuReturnToGame), CP_Image_GetHeight(pMenuReturnToGame), 255);
		}
		break;

	case LOSE:
		CP_Image_Draw(pauseMenuBackground, gameCenterX, gameCenterY, CP_Image_GetWidth(pauseMenuBackground), CP_Image_GetHeight(pauseMenuBackground), 255);
		CP_Image_Draw(loseMenuTitle, gameCenterX, pauseMenuY, CP_Image_GetWidth(loseMenuTitle), CP_Image_GetHeight(loseMenuTitle), 255);

		// Lose Menu Restart
		if (IsAreaClicked(gameCenterX, pMenuRestartY, CP_Image_GetWidth(lMenuRestartWord), CP_Image_GetHeight(lMenuRestartWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuRestartY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(lMenuRestartWordHover, gameCenterX, pMenuRestartY, CP_Image_GetWidth(lMenuRestartWordHover), CP_Image_GetHeight(lMenuRestartWordHover), 255);
		}
		else
		{
			CP_Image_Draw(lMenuRestartWord, gameCenterX, pMenuRestartY, CP_Image_GetWidth(lMenuRestartWord), CP_Image_GetHeight(lMenuRestartWord), 255);
		}

		// Lose Menu Select Level
		if (IsAreaClicked(gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(lMenuSelectLevel), CP_Image_GetHeight(lMenuSelectLevel), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(lMenuSelectLevelHover, gameCenterX, pMenuRtoGameY + 5, CP_Image_GetWidth(lMenuSelectLevelHover), CP_Image_GetHeight(lMenuSelectLevelHover), 255);
		}
		else
		{
			CP_Image_Draw(lMenuSelectLevel, gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(lMenuSelectLevel), CP_Image_GetHeight(lMenuSelectLevel), 255);
		}

		
		break;

	case WIN:
		CP_Image_Draw(pauseMenuBackground, gameCenterX, gameCenterY, CP_Image_GetWidth(pauseMenuBackground), CP_Image_GetHeight(pauseMenuBackground), 255);
		CP_Image_Draw(victoryMenuTitle, gameCenterX, pauseMenuY, CP_Image_GetWidth(victoryMenuTitle), CP_Image_GetHeight(victoryMenuTitle), 255);

		// Victory Menu Next Level
		if (IsAreaClicked(gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(vNextLvlWord), CP_Image_GetHeight(vNextLvlWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(vNextLvlWordHover, gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(vNextLvlWordHover), CP_Image_GetHeight(vNextLvlWordHover), 255);
		}
		else
		{
			CP_Image_Draw(vNextLvlWord, gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(vNextLvlWord), CP_Image_GetHeight(vNextLvlWord), 255);
		}

		// Victory Menu Restart
		if (IsAreaClicked(gameCenterX, pMenuRestartY, CP_Image_GetWidth(vMenuRestartWord), CP_Image_GetHeight(vMenuRestartWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuRestartY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(vMenuRestartWordHover, gameCenterX, pMenuRestartY, CP_Image_GetWidth(vMenuRestartWordHover), CP_Image_GetHeight(vMenuRestartWordHover), 255);
		}
		else
		{
			CP_Image_Draw(vMenuRestartWord, gameCenterX, pMenuRestartY, CP_Image_GetWidth(vMenuRestartWord), CP_Image_GetHeight(vMenuRestartWord), 255);
		}

		// Victory Menu Select Level
		if (IsAreaClicked(gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(vMenuSelectLevelWord), CP_Image_GetHeight(vMenuSelectLevelWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			CP_Image_Draw(pMenuHover, gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(pMenuHover), CP_Image_GetHeight(pMenuHover), 255);
			CP_Image_Draw(vMenuSelectLevelWordHover, gameCenterX, pMenuRtoGameY + 5, CP_Image_GetWidth(vMenuSelectLevelWordHover), CP_Image_GetHeight(vMenuSelectLevelWordHover), 255);
		}
		else
		{
			CP_Image_Draw(vMenuSelectLevelWord, gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(vMenuSelectLevelWord), CP_Image_GetHeight(vMenuSelectLevelWord), 255);
		}
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
void checkClick(void (button1)(void), void(button2)(void), void (button3)(void)) {
	float smallpanelx = 500, smallpanely = 400;

	float panelStartx = 400 - smallpanelx / 2;
	float panelStarty = 400 - smallpanely / 2;

	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
	{
		// --------------------All menu --------------------
		// ----------Button 1---------------------------------------------any button with same size-------------------------------------------------------------------------------
		if ((IsAreaClicked(gameCenterX, pMenuSelectlvlY, CP_Image_GetWidth(pMenuSelectLevelWord), CP_Image_GetHeight(pMenuSelectLevelWord), CP_Input_GetMouseX(), CP_Input_GetMouseY())&&gameState!=LOSE))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			button1();
		}
		// ----------Button 2---------------------------------------------any button with same size-------------------------------------------------------------------------------
		if (IsAreaClicked(gameCenterX, pMenuRestartY, CP_Image_GetWidth(pMenuRestartWord), CP_Image_GetHeight(pMenuRestartWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			button2();
		}
		// ----------Button 3---------------------------------------------any button with same size-------------------------------------------------------------------------------
		if (IsAreaClicked(gameCenterX, pMenuRtoGameY, CP_Image_GetWidth(pMenuReturnToGame), CP_Image_GetHeight(pMenuReturnToGame), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			//buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
			//CP_Sound_PlayAdvanced(buttonSound, 1.0f, 2.0f, FALSE, CP_SOUND_GROUP_2);
			button3();
		}
	}
}

void drawSideBarLevel(char levelNumber[], int noOfStep) {

	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Fill(CP_Color_Create(0,0,0,255));
	CP_Settings_TextSize(40.f);
	CP_Font_DrawTextBox(levelNumber, 810, 30, 200);

	char* number;
	number = malloc(28 + 6);
	if (number != NULL) {
		sprintf_s(number, 34, "Current Number of Steps: %d", noOfStep);
	}
	CP_Settings_TextSize(25.f);
	CP_Font_DrawTextBox(number, 805, 70, 200);

	free(number);
}

void drawSideBarStats(char levelNumber[], int noOfStep) {
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	//drawing title
	CP_Settings_TextSize(40.f);
	CP_Font_DrawTextBox(levelNumber, 810, 30, 200);

	//allocating space
	char* number;
	number = malloc(34);
	//current number of steps
	if (number != NULL) {
		sprintf_s(number, 34, "Current Number of Steps: %d", noOfStep);
	}
	CP_Settings_TextSize(25.f);
	CP_Font_DrawTextBox(number, 805, 70, 200);

	if (player.currentStage > 9) {
		//number of shine
		CP_Settings_TextSize(30.f);
		CP_Font_DrawTextBox("Number of Shine", 810, 200, 200);
		//the exact number
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

		if (player.counter > 500) {
			//number of shine
			CP_Settings_TextSize(30.f);
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawRect(800, 380, 200, 220);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Font_DrawTextBox("If you are having trouble, you can go to settings to turn on easy mode", 810, 400, 200);
		}
	}




	free(number);
}

void freeMenuImages()
{
	//please check again
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	CP_Image_Free(&pauseBackground);

	CP_Image_Free(&pMenuHover);

	CP_Image_Free(&pauseMenuBackground);
	CP_Image_Free(&pauseMenuTitle);

	CP_Image_Free(&pMenuSelectLevelWord);
	CP_Image_Free(&pMenuRestartWord);
	CP_Image_Free(&pMenuReturnToGame);

	CP_Image_Free(&pMenuSelectLevelWordHover);
	CP_Image_Free(&pMenuRestartWordHover);
	CP_Image_Free(&pMenuReturnToGameHover);

	CP_Image_Free(&loseMenuTitle);

	CP_Image_Free(&lMenuRestartWord);
	CP_Image_Free(&lMenuSelectLevel);

	CP_Image_Free(&lMenuRestartWordHover);
	CP_Image_Free(&lMenuSelectLevelHover);

	CP_Image_Free(&victoryMenuTitle);

	CP_Image_Free(&vNextLvlWord);
	CP_Image_Free(&vMenuRestartWord);
	CP_Image_Free(&vMenuSelectLevelWord);

	CP_Image_Free(&vNextLvlWordHover);
	CP_Image_Free(&vMenuRestartWordHover);
	CP_Image_Free(&vMenuSelectLevelWordHover);

	CP_Image_Free(&pauseGradient);

}

void drawSideBarPar(int noOfStep) {

	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));

	char* number;
	number = malloc(28 + 6);
	if (number != NULL) {
		sprintf_s(number, 34, "Par Number of Steps: %d", noOfStep);
	}
	CP_Settings_TextSize(25.f);
	CP_Font_DrawTextBox(number, 805, 120, 200);

	free(number);
}