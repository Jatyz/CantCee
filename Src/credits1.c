//---------------------------------------------------------
// file:	credits1.c
// author:	Ong You Yang
// email:	youyang.o@digipen.edu
//
// brief:	First page of the credits page accessible via the main menu of the game
//			
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright � 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include "utils.h"
#include "game.h"
#include "mainMenu.h"
#include "play.h"
#include "credits1.h"
#include "credits2.h"
#include "settings.h"
#include "howToPlay1.h"

    /*------------------------------------------------------------ Storing Loaded Image in Variable ------------------------------------------------------------*/
CP_Image credits1 = NULL;
CP_Image credits1GradientBackground = NULL;
CP_Image credits1BackToMainMenu = NULL;
CP_Image credits1NextPage = NULL;

void credits1_Init()
{
    /*------------------------------------------------------------ Window Size 1000 x 800 ------------------------------------------------------------*/
    CP_System_SetWindowSize((int)windowWidth, (int)windowHeight);

    /*------------------------------------------------------------ Loading File Path of Image File ------------------------------------------------------------*/
    credits1 = CP_Image_Load("./Assets/credits1.png");
    credits1GradientBackground = CP_Image_Load("./Assets/credits1GradientBackground.png");
    credits1BackToMainMenu = CP_Image_Load("./Assets/credits1BackToMainMenu.png");
    credits1NextPage = CP_Image_Load("./Assets/credits1NextPage.png");
    buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
}

void credits1_Update()
{
    /*------------------------------------------------------------ Checking for MouseInput ------------------------------------------------------------*/
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // --------------- Back to Main Menu Input ---------------
        if (IsAreaClicked(credits1BackButtonX, credits1ButtonY, (float)CP_Image_GetWidth(credits1BackToMainMenu), (float)CP_Image_GetHeight(credits1BackToMainMenu), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
        }

        // --------------- Go to Second Credit Page Input ---------------
        if (IsAreaClicked(credits1NextPageButtonX, credits1ButtonY, (float)CP_Image_GetWidth(credits1NextPage), (float)CP_Image_GetHeight(credits1NextPage), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(credits2_Init, credits2_Update, credits2_Exit);
        }
    }

    /*------------------------------------------------------------ Setting Background Colour ------------------------------------------------------------*/
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    /*------------------------------------------------------------ Drawing/Displaying of Images ------------------------------------------------------------*/
    CP_Image_Draw(credits1GradientBackground, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(credits1, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(credits1BackToMainMenu, credits1BackButtonX, credits1ButtonY, (float)CP_Image_GetWidth(credits1BackToMainMenu), (float)CP_Image_GetHeight(credits1BackToMainMenu), 255);
    CP_Image_Draw(credits1NextPage, credits1NextPageButtonX, credits1ButtonY, (float)CP_Image_GetWidth(credits1NextPage), (float)CP_Image_GetHeight(credits1NextPage), 255);
}

    /*------------------------------------------------------------ Freeing of Images ------------------------------------------------------------*/
void credits1_Exit()
{
    CP_Image_Free(&credits1GradientBackground);
    CP_Image_Free(&credits1);
    CP_Image_Free(&credits1BackToMainMenu);
    CP_Image_Free(&credits1NextPage);
    CP_Sound_Free(&buttonSound);
}
