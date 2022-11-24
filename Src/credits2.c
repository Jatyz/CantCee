//---------------------------------------------------------
// file:	credits2.c
// author:	Ong You Yang
// email:	youyang.o@digipen.edu
//
// brief:	second page of credits
//			
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
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

CP_Image credits2 = NULL;
CP_Image credits2GradientBackground = NULL;
CP_Image credits2BackToMainMenu = NULL;
CP_Image credits2NextPage = NULL;


void credits2_Init()
{
    // Set the window size to a sqaure 1000 x 800
    CP_System_SetWindowSize(windowWidth, windowHeight);

    credits2 = CP_Image_Load("./Assets/credits2.png");
    credits2GradientBackground = CP_Image_Load("./Assets/credits1GradientBackground.png");
    credits2BackToMainMenu = CP_Image_Load("./Assets/credits1BackToMainMenu.png");
    credits2NextPage = CP_Image_Load("./Assets/credits1NextPage.png");
    buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
}

void credits2_Update()
{
    // Background: Black Colour
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    CP_Image_Draw(credits2GradientBackground, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(credits2, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(credits2BackToMainMenu, credits2BackButtonX, credits2ButtonY, CP_Image_GetWidth(credits2BackToMainMenu), CP_Image_GetHeight(credits2BackToMainMenu), 255);
    CP_Image_Draw(credits2NextPage, credits2NextPageButtonX, credits2ButtonY, CP_Image_GetWidth(credits2NextPage), CP_Image_GetHeight(credits2NextPage), 255);

    // -----Checking for MouseInput-----
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // Back To Main Menu Button
        if (IsAreaClicked(credits2BackButtonX, credits2ButtonY, CP_Image_GetWidth(credits2BackToMainMenu), CP_Image_GetHeight(credits2BackToMainMenu), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(credits1_Init, credits1_Update, credits1_Exit);
        }
        if (IsAreaClicked(credits2NextPageButtonX, credits2ButtonY, CP_Image_GetWidth(credits2NextPage), CP_Image_GetHeight(credits2NextPage), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
        }
    }
}

void credits2_Exit()
{
    CP_Image_Free(&credits2GradientBackground);
    CP_Image_Free(&credits2);
    CP_Image_Free(&credits2BackToMainMenu);
    CP_Image_Free(&credits2NextPage);
    CP_Sound_Free(&buttonSound);
}
