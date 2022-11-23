#include "splashscreen.h"
#include "mainmenu.h"

//static variables to be used in this file only
_Bool playing;
int alpha;
float fadeInCounter,fadeOutCounter;
float width;
int vibrationCounter = 0, skipCounter = 0;
CP_Image digipenLogo, zureLogo,Clogo;

void splashscreen_init(void)
{
    //init images
    digipenLogo = CP_Image_Load("Assets/DigiPen_BLACK.png");
    zureLogo = CP_Image_Load("Assets/TeamLogo.png");
    Clogo = CP_Image_Load("Assets/bigclogo.png");    
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    //set window size
    CP_System_SetWindowSize(1000, 800);
    //init values
    playing = 1;
    width = -255;
    fadeOutCounter = 255;
}

void splashscreen_update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

    //code to center image based on digipen logo
    float ImageHeightRatio = (float)CP_Image_GetHeight(digipenLogo) / CP_System_GetDisplayHeight();
    float ImageHeight = (float)ImageHeightRatio * CP_System_GetWindowHeight();
    float ImageWidthRatio = (float)CP_Image_GetWidth(digipenLogo) / CP_System_GetDisplayWidth();
    float ImageWidth = (float)ImageWidthRatio * CP_System_GetWindowWidth();


    //code to move czure logo to center based on resolution as i am doing it based on digipen logo
    float resolutionTenEigthyStaticLogoWidth = 0,resolutionTenEigthyVibrationLogoWidth=0;

    //check if 1920 or 2560
    if (CP_System_GetDisplayWidth() > 2000) {
        resolutionTenEigthyStaticLogoWidth = width * 2.5f;
        resolutionTenEigthyVibrationLogoWidth = width * 2.0f;
    }
    else {
        resolutionTenEigthyStaticLogoWidth = width * 4.5f - 40.0f;
        resolutionTenEigthyVibrationLogoWidth = width * 3.0f;
    }

    //if image is not centered
    if(width< (CP_System_GetWindowWidth() - ImageWidth) / 2)
        width += CP_System_GetDt() * (255 / FadeInSeconds)*3;

    //after image fades in
    if (fadeInCounter > 254) {
        //check shake count
        if (vibrationCounter < 20) {
            skipCounter = 1;
            if (playing) {
                CP_Image_DrawAdvanced(digipenLogo, width, ((CP_System_GetWindowHeight() - ImageHeight) / 2.f) - vibrationCounter, ImageWidth, ImageHeight, 255, 0);
                playing = !playing;
                vibrationCounter++;
            }
            else {
                CP_Image_DrawAdvanced(digipenLogo, width, ((CP_System_GetWindowHeight() - ImageHeight) / 2.f) + vibrationCounter, ImageWidth, ImageHeight, 255, 0);
                playing = !playing;
                vibrationCounter++;
            }
        }
        else {
            //check shake count
            if (vibrationCounter < 40) {
                if (playing) {
                    CP_Image_DrawAdvanced(zureLogo, resolutionTenEigthyVibrationLogoWidth, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2) - 20, ImageWidth / 2, ImageHeight / 2, 255, 0);
                    playing = !playing;
                    vibrationCounter++;
                }
                else {
                    CP_Image_DrawAdvanced(zureLogo, resolutionTenEigthyVibrationLogoWidth, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2) + 20, ImageWidth / 2, ImageHeight / 2, 255, 0);
                    playing = !playing;
                    vibrationCounter++;
                }
            }
            else {//fade out logo once fade count more than 40
                skipCounter = 2;
                fadeOutCounter -= CP_System_GetDt() * (255 / FadeInSeconds);
                alpha = ((int)fadeOutCounter % 255);
                CP_Image_DrawAdvanced(Clogo, width+70.f, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2)-120.f, 300, 300, alpha, 0);
                CP_Image_DrawAdvanced(zureLogo,resolutionTenEigthyStaticLogoWidth, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2) -10, ImageWidth / 2, ImageHeight / 2, alpha, 0);

                //change scene once faded out
                if (fadeOutCounter < 0) {
                    CP_Engine_SetNextGameState(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
                }

            }
        }

    }
    else {
        //fade in if alpha not 255
        fadeInCounter += CP_System_GetDt() * (255 / FadeInSeconds);
        alpha = ((int)fadeInCounter % 255);
        CP_Image_DrawAdvanced(digipenLogo, width, (CP_System_GetWindowHeight() - ImageHeight) / 2, ImageWidth, ImageHeight, alpha, 0);
    }


    //skip counter so people can skip intro screens
    if (CP_Input_KeyTriggered(KEY_SPACE)) {
        skipCounter++;
        switch (skipCounter) {
        case 1:
            fadeInCounter = 255;
            width = (CP_System_GetWindowWidth() - ImageWidth) / 2;
            break;
        case 2:
            vibrationCounter = 39;
            break;
        case 3:
            fadeOutCounter = 0;
            break;
        }
    }
}

//things to be do on exit
void splashscreen_exit(void) {
    CP_Settings_ImageMode(CP_POSITION_CENTER);
    CP_Image_Free(&digipenLogo);
    CP_Image_Free(&Clogo);
    CP_Image_Free(&zureLogo);
}
