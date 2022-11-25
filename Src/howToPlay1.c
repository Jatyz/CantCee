//---------------------------------------------------------
// file:	howToPlay1.c
// author:  Ong You Yang
// email:   youyang.o@digipen.edu
//
// brief:	How to play contains the general instructions & controls of the game accesible via the Main Menu
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
#include "settings.h"
#include "howToPlay1.h"

    /*------------------------------------------------------------ Storing Loaded Image in Variable ------------------------------------------------------------*/
CP_Image howToPlay1 = NULL;
CP_Image howToPlay2 = NULL;
CP_Image howToPlay1BackToMainMenu = NULL;
CP_Image howToPlay1NextPage = NULL;

CP_Image HTPBackground = NULL;

CP_Image gradientAccentBackground3 = NULL;

int swap = 0;

void howToPlay1_Init()
{
    /*------------------------------------------------------------ Window Size 1000 x 800 ------------------------------------------------------------*/
    CP_System_SetWindowSize((int)windowWidth, (int)windowHeight);

    /*------------------------------------------------------------ Loading File Path of Image File ------------------------------------------------------------*/
    howToPlay1 = CP_Image_Load("./Assets/howToPlay1.png");
    howToPlay2 = CP_Image_Load("./Assets/howToPlay2.png");
    howToPlay1BackToMainMenu = CP_Image_Load("./Assets/howToPlay1BackToMainMenu.png");
    howToPlay1NextPage = CP_Image_Load("./Assets/howToPlay1NextPage.png");
    HTPBackground = CP_Image_Load("./Assets/HTPBackground.png");

    buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");

    gradientAccentBackground3 = CP_Image_Load("./Assets/gradientAccentBackground3.png");
}

void howToPlay1_Update()
{
    /*------------------------------------------------------------ Checking for MouseInput ------------------------------------------------------------*/
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // --------------- Next Page Mouse Input ---------------
        if (IsAreaClicked(htp1NPX, htp1NPY, (float)CP_Image_GetWidth(howToPlay1NextPage), (float)CP_Image_GetHeight(howToPlay1NextPage), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            if(!swap)
            {
            swap = !swap;
            return;
            }
            swap = 0;
            //CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
        }

        // --------------- Swap Back to Previous Page ---------------
        if (IsAreaClicked(htp1BTMMx, htp1BTMMy, (float)CP_Image_GetWidth(howToPlay1NextPage), (float)CP_Image_GetHeight(howToPlay1NextPage), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            if (swap)
            {
                swap = !swap;
                return;
            }
            swap = 0;
            CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
        }
    }

    /*------------------------------------------------------------ Setting Background Colour ------------------------------------------------------------*/
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    /*------------------------------------------------------------ Drawing/Displaying of Images ------------------------------------------------------------*/
    // --------------- Background of HowToPlay ---------------
    CP_Image_Draw(HTPBackground, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(gradientAccentBackground3, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    // --------------- First Page of HowToPlay ---------------
    if (!swap)
    {
        CP_Image_Draw(howToPlay1, windowWidth / 2, windowHeight / 2, (float)CP_Image_GetWidth(howToPlay1), (float)CP_Image_GetHeight(howToPlay1), 255);
        CP_Image_Draw(howToPlay1BackToMainMenu, htp1BTMMx, htp1BTMMy, (float)CP_Image_GetWidth(howToPlay1BackToMainMenu), (float)CP_Image_GetHeight(howToPlay1BackToMainMenu), 255);
        CP_Image_Draw(howToPlay1NextPage, htp1NPX, htp1NPY, (float)CP_Image_GetWidth(howToPlay1NextPage), (float)CP_Image_GetHeight(howToPlay1NextPage), 255);
    }

    // --------------- Second Page of HowToPlay ---------------
    else
    {
        CP_Image_Draw(howToPlay2, windowWidth / 2, windowHeight / 2, (float)CP_Image_GetWidth(howToPlay2), (float)CP_Image_GetHeight(howToPlay2), 255);
        CP_Image_Draw(howToPlay1BackToMainMenu, htp1BTMMx, htp1BTMMy, (float)CP_Image_GetWidth(howToPlay1BackToMainMenu), (float)CP_Image_GetHeight(howToPlay1BackToMainMenu), 255);
        CP_Image_Draw(howToPlay1NextPage, htp1NPX, htp1NPY, (float)CP_Image_GetWidth(howToPlay1NextPage), (float)CP_Image_GetHeight(howToPlay1NextPage), 255);
    }
}

    /*------------------------------------------------------------ Freeing of Images ------------------------------------------------------------*/
void howToPlay1_Exit()
{
    CP_Image_Free(&howToPlay1);
    CP_Image_Free(&howToPlay2);
    CP_Image_Free(&howToPlay1BackToMainMenu);
    CP_Image_Free(&howToPlay1NextPage);
    CP_Image_Free(&HTPBackground);
    CP_Image_Free(&gradientAccentBackground3);

    CP_Sound_Free(&buttonSound);
}

