#include "cprocessing.h"
#include "utils.h"

#include "mainMenu.h"
#include "play.h"
#include "settings.h"
#include "howToPlay.h"

CP_Image wButton = NULL;
CP_Image aButton = NULL;
CP_Image sButton = NULL;
CP_Image dButton = NULL;
CP_Image eButton = NULL;
CP_Image qButton = NULL;

CP_Image returnToMainMenu = NULL;

void howToPlay_Init()
{
    // Set the window size to a sqaure 1000 x 800
    CP_System_SetWindowSize(windowWidth, windowHeight);

    // Set the rectangle drawing mode to CENTER
    CP_Settings_RectMode(CP_POSITION_CENTER);

    // All Text size
    CP_Settings_TextSize(20.0f);

    // All Text allignment
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    wButton = CP_Image_Load("./Assets/wButton.png");
    aButton = CP_Image_Load("./Assets/aButton.png");
    sButton = CP_Image_Load("./Assets/sButton.png");
    dButton = CP_Image_Load("./Assets/dButton.png");
    qButton = CP_Image_Load("./Assets/qButton.png");
    eButton = CP_Image_Load("./Assets/eButton.png");

    returnToMainMenu = CP_Image_Load("./Assets/returnToMainMenu.png");

}

void howToPlay_Update()
{
    // Background: Black Colour
    CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 255));

    CP_Image_Draw(wButton, wButtonX, wButtonY, CP_Image_GetWidth(wButton), CP_Image_GetHeight(wButton), 255);
    CP_Image_Draw(aButton, aButtonX, asdButtonY, CP_Image_GetWidth(aButton), CP_Image_GetHeight(aButton), 255);
    CP_Image_Draw(sButton, sButtonX, asdButtonY, CP_Image_GetWidth(sButton), CP_Image_GetHeight(sButton), 255);
    CP_Image_Draw(dButton, dButtonX, asdButtonY, CP_Image_GetWidth(dButton), CP_Image_GetHeight(dButton), 255);
    CP_Image_Draw(qButton, qButtonX, qeButtonY, CP_Image_GetWidth(qButton), CP_Image_GetHeight(qButton), 255);
    CP_Image_Draw(eButton, eButtonX, qeButtonY, CP_Image_GetWidth(eButton), CP_Image_GetHeight(eButton), 255);

    CP_Image_Draw(returnToMainMenu, returnToMainMenuX, returnToMainMenuY, CP_Image_GetWidth(returnToMainMenu), CP_Image_GetHeight(returnToMainMenu), 255);


	// How To Play Text
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("How To Play", (windowWidth / 2.0f), (windowHeight / 2.0f - 350));

	//// Placeholder W
 //   CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
 //   CP_Graphics_DrawRect(windowWidth / 2.0f - 100, (windowHeight / 2.0f - 100), buttonWidth, buttonHeight);
 //   CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
 //   CP_Font_DrawText("W", windowWidth / 2.0f - 100, (windowHeight / 2.0f) - 100);
    

// -----Checking for MouseInput-----
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // exitButton
        if (IsAreaClicked(returnToMainMenuX, returnToMainMenuY, CP_Image_GetWidth(returnToMainMenu), CP_Image_GetHeight(returnToMainMenu), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
        }
    }
    //if (IsAreaClicked(secondColumn, firstRowHeight, levelButtonWidth, levelButtonHeight, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
    //{
    //	CP_Engine_SetNextGameStateForced(level2_init, level2_update, level2_exit);
    //}


}

void howToPlay_Exit()
{
    CP_Image_Free(&wButton);
    CP_Image_Free(&aButton);
    CP_Image_Free(&sButton);
    CP_Image_Free(&dButton);
    CP_Image_Free(&qButton);
    CP_Image_Free(&eButton);

    CP_Image_Free(&returnToMainMenu);

}
