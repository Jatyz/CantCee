#include "cprocessing.h"
#include "utils.h"

#include "mainmenu.h"
#include "play.h"
#include "howToPlay.h"
#include "settings.h"

CP_Image background;
int concurrent_Alpha = 0;

// ---------------------------------------------------------------Main Menu Initialisation---------------------------------------------------------------
void mainMenu_Init()    
{


    // Set the window size to a sqaure 800 x 800
    CP_System_SetWindowSize(windowWidth, windowHeight);

    // Set the rectangle drawing mode to CENTER
    CP_Settings_RectMode(CP_POSITION_CENTER);

    // All Text size
    CP_Settings_TextSize(20.0f);

    // All Text allignment
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}


// ---------------------------------------------------------------Main Menu Update---------------------------------------------------------------
void mainMenu_Update()
{

    //background = CP_Image_Load("Assets/mainMenuBackground.png");
    //CP_Settings_ImageMode(CP_POSITION_CORNER);
    //CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

    //CP_System_SetWindowSize(CP_Image_GetWidth(background), CP_Image_GetHeight(background));
    // 
    // Background: Grey Colour
    CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 255));

    // -----Play Button-----
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(windowWidth / 2.0f, (windowHeight / 2.0f - 150), buttonWidth, buttonHeight);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Play", windowWidth / 2.0f, (windowHeight / 2.0f) - 150);
    
    // -----How to Play-----
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(windowWidth / 2.0f, (windowHeight / 2.0f - 50), buttonWidth, buttonHeight);                     
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("How to Play", windowWidth / 2.0f, (windowHeight / 2.0f) - 50);

    // -----Settings-----
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));                                                                   
    CP_Graphics_DrawRect(windowWidth / 2.0f, (windowHeight / 2.0f + 50), buttonWidth, buttonHeight);                     
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Options", windowWidth / 2.0f, (windowHeight / 2.0f) + 50);

    // -----Exit Button-----
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(windowWidth / 2.0f, (windowHeight / 2.0f) + 150, buttonWidth, buttonHeight);                    
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Exit", windowWidth / 2.0f, (windowHeight / 2.0f) + 150);



// ---------------------------------------------------------------Mouse Inputs/Checking---------------------------------------------------------------
    // -----Checking for MouseInput-----
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {   
        // -----Play Button Input-----
        if (IsAreaClicked(windowWidth / 2.0f, (windowHeight / 2.0f) - 150, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(play_Init, play_Update, play_Exit); // play.c > goes to level select > click level to play
        }

        // -----How to Play Input-----
        if (IsAreaClicked(windowWidth / 2.0f, (windowHeight / 2.0f) - 50, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(howToPlay_Init, howToPlay_Update, howToPlay_Exit); // change to an addition howToPlay.c
        }

        // -----Settings Input-----
        if (IsAreaClicked(windowWidth / 2.0f, (windowHeight / 2.0f) + 50, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(settings_Init, settings_Update, settings_Exit); // change to an addition options.c
        }

        // -----Exit Button Input-----
        if (IsAreaClicked(windowWidth / 2.0f, (windowHeight / 2.0f) + 150, buttonWidth, buttonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_Terminate();
        }
    }
}


// ---------------------------------------------------------------Main Menu Exit---------------------------------------------------------------
void mainMenu_Exit() 
{

}
