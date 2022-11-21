#include "cprocessing.h"
#include "utils.h"

#include "mainmenu.h"

#include "play.h"
#include "howToPlay1.h"
#include "credits1.h"
#include "settings.h"

#include "game.h"

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


// ---------------------------------------------------------------Main Menu Initialisation---------------------------------------------------------------
void mainMenu_Init()
{   
    CP_System_SetWindowTitle("CANT CEE");

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

    // Set the window size to a sqaure 1000 x 800
    CP_System_SetWindowSize(windowWidth, windowHeight);

    // Set the rectangle drawing mode to CENTER
    CP_Settings_RectMode(CP_POSITION_CENTER);

    // All Text size
    CP_Settings_TextSize(20.0f);

    // All Text allignment
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    createScore();

    readScore();
}


// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void mainMenu_Update()
{
    // Background: Grey Colour
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    CP_Image_Draw(mainMenuBackground1, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    CP_Image_Draw(cLogo, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(cant, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(cee, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    CP_Image_Draw(bracket, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);
    CP_Image_Draw(gradientAccentBackground, windowWidth / 2, windowHeight / 2, windowWidth, windowHeight, 255);

    CP_Image_Draw(startWord, startWordWidth, startWordHeight, CP_Image_GetWidth(startWord), CP_Image_GetHeight(startWord), 255);
    CP_Image_Draw(howToPlayWord, howToPlayWordWidth, howToPlayWordHeight, CP_Image_GetWidth(howToPlayWord), CP_Image_GetHeight(howToPlayWord), 255);
    CP_Image_Draw(creditsWord, creditsWordWidth, creditsWordHeight, CP_Image_GetWidth(creditsWord), CP_Image_GetHeight(creditsWord), 255);
    CP_Image_Draw(settingsWord, settingsWordWidth, settingsWordHeight, CP_Image_GetWidth(settingsWord), CP_Image_GetHeight(settingsWord), 255);
    CP_Image_Draw(exitWord, exitWordWidth, exitWordHeight, CP_Image_GetWidth(exitWord), CP_Image_GetHeight(exitWord), 255);



    // ---------------------------------------------------------------Mouse Inputs/Checking---------------------------------------------------------------
        // ----------Hover Feature----------
    if (IsAreaClicked(startWordWidth, startWordHeight, CP_Image_GetWidth(startWord), CP_Image_GetHeight(startWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverStart, startWordWidth - 5, startWordHeight - 5, CP_Image_GetWidth(startWord), CP_Image_GetHeight(startWord), 255);
        CP_Image_Draw(hoverStartWord, startWordWidth, startWordHeight, CP_Image_GetWidth(startWord), CP_Image_GetHeight(startWord), 255);
    }

    if (IsAreaClicked(howToPlayWordWidth, howToPlayWordHeight, CP_Image_GetWidth(hoverHowToPLay), CP_Image_GetHeight(hoverHowToPLay), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverHowToPLay, howToPlayWordWidth - 5, howToPlayWordHeight - 5, CP_Image_GetWidth(hoverHowToPLay), CP_Image_GetHeight(hoverHowToPLay), 255);
    }

    if (IsAreaClicked(creditsWordWidth, creditsWordHeight, CP_Image_GetWidth(creditsWord), CP_Image_GetHeight(creditsWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverCredits, creditsWordWidth - 5, creditsWordHeight - 5, CP_Image_GetWidth(hoverCredits), CP_Image_GetHeight(hoverCredits), 255);
    }

    if (IsAreaClicked(settingsWordWidth, settingsWordHeight, CP_Image_GetWidth(creditsWord), CP_Image_GetHeight(creditsWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverSettings, settingsWordWidth - 5, settingsWordHeight - 5, CP_Image_GetWidth(hoverSettings), CP_Image_GetHeight(hoverSettings), 255);
    }

    if (IsAreaClicked(exitWordWidth, exitWordHeight, CP_Image_GetWidth(creditsWord), CP_Image_GetHeight(creditsWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
    {
        CP_Image_Draw(hoverExit, exitWordWidth - 5, exitWordHeight - 5, CP_Image_GetWidth(hoverExit), CP_Image_GetHeight(hoverExit), 255);
    }


    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // ----------Play Button Input----------
        if (IsAreaClicked(startWordWidth, startWordHeight, CP_Image_GetWidth(startWord), CP_Image_GetHeight(startWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(play_Init, play_Update, play_Exit); // play.c > goes to level select > click level to play
        }

        // ----------How to Play Input----------
        if (IsAreaClicked(howToPlayWordWidth, howToPlayWordHeight, CP_Image_GetWidth(howToPlayWord), CP_Image_GetHeight(howToPlayWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(howToPlay1_Init, howToPlay1_Update, howToPlay1_Exit);
        }

        // ----------Credit Input----------
        if (IsAreaClicked(creditsWordWidth, creditsWordHeight, CP_Image_GetWidth(creditsWord), CP_Image_GetHeight(creditsWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(credits1_Init, credits1_Update, credits1_Exit);
        }

        // ----------Settings Input----------
        if (IsAreaClicked(settingsWordWidth, settingsWordHeight, CP_Image_GetWidth(settingsWord), CP_Image_GetHeight(settingsWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(settings_Init, settings_Update, settings_Exit);
        }

        // ----------Exit Button Input----------
        if (IsAreaClicked(exitWordWidth, exitWordHeight, CP_Image_GetWidth(exitWord), CP_Image_GetHeight(exitWord), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_Terminate();
        }
    }
}


// ---------------------------------------------------------------Main Menu Exit---------------------------------------------------------------
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
}
