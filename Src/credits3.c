//---------------------------------------------------------
// file:	credits3.c
// author:	Ong You Yang
// email:	youyang.o@digipen.edu
//
// brief:	Third page of the credits page ONLY accessible via the Second credits page. Its about crediting copyrights
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
#include "credits3.h"
#include "settings.h"
#include "howToPlay1.h"

    /*------------------------------------------------------------ Storing Loaded Image in Variable ------------------------------------------------------------*/
CP_Image copyrights = NULL;
CP_Image credits3GradientBackground = NULL;
CP_Image copyrights2 = NULL;

CP_Image credits3BackToMainMenu = NULL;
CP_Image credits3NextPage = NULL;


void credits3_Init()
{
    /*------------------------------------------------------------ Window Size 1000 x 800 ------------------------------------------------------------*/
    CP_System_SetWindowSize((int)windowWidth, (int)windowHeight);

    /*------------------------------------------------------------ Loading File Path of Image File ------------------------------------------------------------*/
    copyrights = CP_Image_Load("./Assets/copyrights.png");
    credits3GradientBackground = CP_Image_Load("./Assets/credits3GradientBackground.png");
    copyrights2 = CP_Image_Load("./Assets/copyrights2.png");

    credits3BackToMainMenu = CP_Image_Load("./Assets/credits3BackToMainMenu.png");
    credits3NextPage = CP_Image_Load("./Assets/credits3NextPage.png");

    buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
}

void credits3_Update()
{
    /*------------------------------------------------------------ Checking for MouseInput ------------------------------------------------------------*/
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // --------------- Back to First Credit Page Input ---------------
        if (IsAreaClicked(credits3BackButtonX, credits3ButtonY, (float)CP_Image_GetWidth(credits3BackToMainMenu), (float)CP_Image_GetHeight(credits3BackToMainMenu), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(credits1_Init, credits1_Update, credits1_Exit);
        }

        // --------------- Go to Main Menu Input ---------------
        if (IsAreaClicked(credits3NextPageButtonX, credits3ButtonY, (float)CP_Image_GetWidth(credits3NextPage), (float)CP_Image_GetHeight(credits3NextPage), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
        }
    }

    /*------------------------------------------------------------ Setting Background Colour ------------------------------------------------------------*/
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    /*------------------------------------------------------------ Drawing/Displaying of Images ------------------------------------------------------------*/
    CP_Image_Draw(copyrights, windowWidth /2, windowHeight/2, (float)CP_Image_GetWidth(copyrights), (float)CP_Image_GetHeight(copyrights), 255);
    CP_Image_Draw(credits3GradientBackground, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(copyrights2, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    CP_Image_Draw(credits3BackToMainMenu, credits2BackButtonX, credits2ButtonY, (float)CP_Image_GetWidth(credits3BackToMainMenu), (float)CP_Image_GetHeight(credits3BackToMainMenu), 255);
    CP_Image_Draw(credits3NextPage, credits2NextPageButtonX, credits2ButtonY, (float)CP_Image_GetWidth(credits3NextPage), (float)CP_Image_GetHeight(credits3NextPage), 255);

}

    /*------------------------------------------------------------ Freeing of Images ------------------------------------------------------------*/
void credits3_Exit()
{
    CP_Image_Free(&copyrights);
    CP_Image_Free(&credits3GradientBackground);
    CP_Image_Free(&copyrights2);

    CP_Image_Free(&credits3BackToMainMenu);
    CP_Image_Free(&credits3NextPage);
}
