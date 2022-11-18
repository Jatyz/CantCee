#include "cprocessing.h"
#include "utils.h"

#include "mainMenu.h"
#include "play.h"
#include "settings.h"
#include "howToPlay2.h"
#include "credits1.h"

CP_Image howToPlay1 = NULL;
CP_Image howToPlay2 = NULL;
CP_Image howToPlay1BackToMainMenu = NULL;

int swap = 0;

void howToPlay1_Init()
{
    // Set the window size to a sqaure 1000 x 800
    CP_System_SetWindowSize(windowWidth, windowHeight);

    // Set the rectangle drawing mode to CENTER
   

    howToPlay1 = CP_Image_Load("./Assets/howToPlay1.png");
    howToPlay2 = CP_Image_Load("./Assets/howToPlay2.png");
    howToPlay1BackToMainMenu = CP_Image_Load("./Assets/howToPlay1BackToMainMenu.png");
}

void howToPlay1_Update()
{
    // Background: Black Colour
    CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 255));
    if (!swap) {
        CP_Image_Draw(howToPlay1, windowWidth / 2, windowHeight / 2, CP_Image_GetWidth(howToPlay1), CP_Image_GetHeight(howToPlay1), 255);
        CP_Image_Draw(howToPlay1BackToMainMenu, windowWidth / 2, windowHeight / 2, CP_Image_GetWidth(howToPlay1BackToMainMenu), CP_Image_GetHeight(howToPlay1BackToMainMenu), 255);
    }
    else {
        //how to play 2 image
        CP_Image_Draw(howToPlay2, windowWidth / 2, windowHeight / 2, CP_Image_GetWidth(howToPlay2), CP_Image_GetHeight(howToPlay2), 255);

    }

    //if arrow on click
  //  {
    //swap = !swap;

    // -----Checking for MouseInput-----
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT) == 1)
    {
        // Back To Main Menu Button
        if (IsAreaClicked(100, 100, CP_Image_GetWidth(howToPlay1BackToMainMenu), CP_Image_GetHeight(howToPlay1BackToMainMenu), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        {
            swap = !swap;
            //CP_Engine_SetNextGameStateForced(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
        }
        //if (IsAreaClicked(credits1NextPageButtonX, credits1ButtonY, CP_Image_GetWidth(credits1NextPage), CP_Image_GetHeight(credits1NextPage), CP_Input_GetMouseX(), CP_Input_GetMouseY()))
        //{
        //    CP_Engine_SetNextGameStateForced(credits2_Init, credits2_Update, credits2_Exit);
        //}
    
    }


}

void howToPlay1_Exit()
{
    CP_Image_Free(&howToPlay1);


 
}

