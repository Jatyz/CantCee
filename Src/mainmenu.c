//---------------------------------------------------------
// file:	mainmenu.c
// author:	Ong You Yang
// email:	youyang.o@digipen.edu
//
// brief:	Main menu
//			
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright � 2022 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include "utils.h"

#include "mainmenu.h"
#include "play.h"
#include "howToPlay1.h"
#include "credits1.h"
#include "settings.h"

#include "game.h"

    /*------------------------------------------------------------ Storing Loaded Image in Variable ------------------------------------------------------------*/
CP_Image mainMenuBackground1 = NULL;

CP_Image cLogo = NULL;
CP_Image cant = NULL;
CP_Image cee = NULL;

CP_Image bracket = NULL;
CP_Image gradientAccentBackground = NULL;

CP_Image startWord = NULL;
CP_Image howToPlayWord = NULL;
CP_Image creditsWord = NULL;
CP_Image settingsWord = NULL;
CP_Image exitWord = NULL;

CP_Image hoverStart = NULL;
CP_Image hoverHowToPLay = NULL;
CP_Image hoverCredits = NULL;
CP_Image hoverSettings = NULL;
CP_Image hoverExit = NULL;

CP_Image hoverStartWord = NULL;


// --------------------------------------------------------------- Main Menu Initialisation ---------------------------------------------------------------
void mainMenu_Init()
{   
    /*------------------------------------------------------------ Window Size 1000 x 800 ------------------------------------------------------------*/
    CP_System_SetWindowSize((int)windowWidth, (int)windowHeight);

    CP_System_SetWindowTitle("CANT CEE");

    createScore();
    readScore();

    /*------------------------------------------------------------ Loading File Path of Image File ------------------------------------------------------------*/
    mainMenuBackground1 = CP_Image_Load("./Assets/mainMenuBackground1.png");

    cLogo = CP_Image_Load("./Assets/cLogo.png");
    cant = CP_Image_Load("./Assets/cant.png");
    cee = CP_Image_Load("./Assets/cee.png");

    bracket = CP_Image_Load("./Assets/bracket.png");
    gradientAccentBackground = CP_Image_Load("./Assets/gradientAccentBackground.png");

    startWord = CP_Image_Load("./Assets/startWord.png");
    howToPlayWord = CP_Image_Load("./Assets/howToPlayWord.png");
    creditsWord = CP_Image_Load("./Assets/creditsWord.png");
    settingsWord = CP_Image_Load("./Assets/settingsWord.png");
    exitWord = CP_Image_Load("./Assets/exitWord.png");

    hoverStart = CP_Image_Load("./Assets/hoverStart.png");
    hoverHowToPLay = CP_Image_Load("./Assets/hoverHowToPlay.png");
    hoverCredits = CP_Image_Load("./Assets/hoverCredits.png");
    hoverSettings = CP_Image_Load("./Assets/hoverSettings.png");
    hoverExit = CP_Image_Load("./Assets/hoverExit.png");

    hoverStartWord = CP_Image_Load("./Assets/hoverStartWord.png");

    buttonSound = CP_Sound_Load("./Assets/Sounds/Button Sound.mp3");
}


// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void mainMenu_Update()
{
    /*------------------------------------------------------------ Setting Background Colour ------------------------------------------------------------*/
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    /*------------------------------------------------------------ Drawing/Displaying of Images ------------------------------------------------------------*/
    CP_Image_Draw(mainMenuBackground1, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    CP_Image_Draw(cLogo, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(cant, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(cee, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    CP_Image_Draw(bracket, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(gradientAccentBackground, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    CP_Image_Draw(startWord, startWordWidth, startWordHeight, (float)CP_Image_GetWidth(startWord), (float)CP_Image_GetHeight(startWord), 255);
    CP_Image_Draw(howToPlayWord, howToPlayWordWidth, howToPlayWordHeight, (float)CP_Image_GetWidth(howToPlayWord), (float)CP_Image_GetHeight(howToPlayWord), 255);
    CP_Image_Draw(creditsWord, creditsWordWidth, creditsWordHeight, (float)CP_Image_GetWidth(creditsWord), (float)CP_Image_GetHeight(creditsWord), 255);
    CP_Image_Draw(settingsWord, settingsWordWidth, settingsWordHeight, (float)CP_Image_GetWidth(settingsWord), (float)CP_Image_GetHeight(settingsWord), 255);
    CP_Image_Draw(exitWord, exitWordWidth, exitWordHeight, (float)CP_Image_GetWidth(exitWord), (float)CP_Image_GetHeight(exitWord), 255);

    // ---------------------------------------------------------------Mouse Inputs/Checking---------------------------------------------------------------
    // --------------- Hover Feature ---------------
    if (IsAreaClicked(startWordWidth, startWordHeight, (float)CP_Image_GetWidth(startWord), (float)CP_Image_GetHeight(startWord), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverStart, startWordWidth - 5, startWordHeight - 5, (float)CP_Image_GetWidth(startWord), (float)CP_Image_GetHeight(startWord), 255);
        CP_Image_Draw(hoverStartWord, startWordWidth, startWordHeight, (float)CP_Image_GetWidth(startWord), (float)CP_Image_GetHeight(startWord), 255);
    }

    if (IsAreaClicked(howToPlayWordWidth, howToPlayWordHeight, (float)CP_Image_GetWidth(hoverHowToPLay), (float)CP_Image_GetHeight(hoverHowToPLay), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverHowToPLay, howToPlayWordWidth - 5, howToPlayWordHeight - 5, (float)CP_Image_GetWidth(hoverHowToPLay), (float)CP_Image_GetHeight(hoverHowToPLay), 255);
    }

    if (IsAreaClicked(creditsWordWidth, creditsWordHeight, (float)CP_Image_GetWidth(creditsWord), (float)CP_Image_GetHeight(creditsWord), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverCredits, creditsWordWidth - 5, creditsWordHeight - 5, (float)CP_Image_GetWidth(hoverCredits), (float)CP_Image_GetHeight(hoverCredits), 255);
    }

    if (IsAreaClicked(settingsWordWidth, settingsWordHeight, (float)CP_Image_GetWidth(creditsWord), (float)CP_Image_GetHeight(creditsWord), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverSettings, settingsWordWidth - 5, settingsWordHeight - 5, (float)CP_Image_GetWidth(hoverSettings), (float)CP_Image_GetHeight(hoverSettings), 255);
    }

    if (IsAreaClicked(exitWordWidth, exitWordHeight, (float)CP_Image_GetWidth(creditsWord), (float)CP_Image_GetHeight(creditsWord), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverExit, exitWordWidth - 5, exitWordHeight - 5, (float)CP_Image_GetWidth(hoverExit), (float)CP_Image_GetHeight(hoverExit), 255);
    }

    // --------------- Mouse Input ---------------
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // ----------Play Button Input----------
        if (IsAreaClicked(startWordWidth, startWordHeight, (float)CP_Image_GetWidth(startWord), (float)CP_Image_GetHeight(startWord), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(play_Init, play_Update, play_Exit); // play.c > goes to level select > click level to play
        }

        // ----------How to Play Input----------
        if (IsAreaClicked(howToPlayWordWidth, howToPlayWordHeight, (float)CP_Image_GetWidth(howToPlayWord), (float)CP_Image_GetHeight(howToPlayWord), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(howToPlay1_Init, howToPlay1_Update, howToPlay1_Exit);
        }

        // ----------Credit Input----------
        if (IsAreaClicked(creditsWordWidth, creditsWordHeight, (float)CP_Image_GetWidth(creditsWord), (float)CP_Image_GetHeight(creditsWord), (float)CP_Input_GetMouseX(), (float)CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(credits1_Init, credits1_Update, credits1_Exit);
        }

        // ----------Settings Input----------
        if (IsAreaClicked(settingsWordWidth, settingsWordHeight, (float)CP_Image_GetWidth(settingsWord), (float)CP_Image_GetHeight(settingsWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_SetNextGameStateForced(settings_Init, settings_Update, settings_Exit);
        }

        // ----------Exit Button Input----------
        if (IsAreaClicked(exitWordWidth, exitWordHeight, (float)CP_Image_GetWidth(exitWord), (float)CP_Image_GetHeight(exitWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Sound_PlayAdvanced(buttonSound, CP_Sound_GetGroupVolume(CP_SOUND_GROUP_SFX), 2.0f, FALSE, CP_SOUND_GROUP_SFX);
            CP_Engine_Terminate();
        }
    }
}


    /*------------------------------------------------------------ Freeing of Images ------------------------------------------------------------*/
void mainMenu_Exit()
{
    CP_Image_Free(&mainMenuBackground1);

    CP_Image_Free(&cLogo);
    CP_Image_Free(&cant);
    CP_Image_Free(&cee);

    CP_Image_Free(&bracket);
    CP_Image_Free(&gradientAccentBackground);

    CP_Image_Free(&startWord);
    CP_Image_Free(&howToPlayWord);
    CP_Image_Free(&creditsWord);
    CP_Image_Free(&settingsWord);
    CP_Image_Free(&exitWord);

    CP_Image_Free(&hoverStart);
    CP_Image_Free(&hoverHowToPLay);
    CP_Image_Free(&hoverCredits);
    CP_Image_Free(&hoverSettings);
    CP_Image_Free(&hoverExit);

    CP_Image_Free(&hoverStartWord);

    CP_Sound_Free(&buttonSound);
}
