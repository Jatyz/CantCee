#include "splashscreen.h"
#include "mainmenu.h"
_Bool playing;
int alpha;
double counter,counter3;
float width;
int counter2 = 0;
CP_Image logo, logo2,logo3;
void splashscreen_init(void)
{
    logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
    logo2 = CP_Image_Load("Assets/TeamLogo.png");
    logo3 = CP_Image_Load("Assets/bigclogo.png");    
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_System_SetWindowSize(1000, 800);
    playing = 1;
    width = -255;
    counter3 = 255;
}

void splashscreen_update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));


    float ImageHeightRatio = (float)CP_Image_GetHeight(logo) / CP_System_GetDisplayHeight();
    float ImageHeight = (float)ImageHeightRatio * CP_System_GetWindowHeight();
    float ImageWidthRatio = (float)CP_Image_GetWidth(logo) / CP_System_GetDisplayWidth();
    float ImageWidth = (float)ImageWidthRatio * CP_System_GetWindowWidth();

    if(width< (CP_System_GetWindowWidth() - ImageWidth) / 2)
        width += CP_System_GetDt() * (255 / FadeInSeconds)*3;

    if (counter > 254) {
        if (counter2 < 20) {
            if (playing) {
                CP_Image_DrawAdvanced(logo, width, ((CP_System_GetWindowHeight() - ImageHeight) / 2) - counter2, ImageWidth, ImageHeight, 255, 0);
                playing = !playing;
                counter2++;
            }
            else {
                CP_Image_DrawAdvanced(logo, width, ((CP_System_GetWindowHeight() - ImageHeight) / 2) + counter2, ImageWidth, ImageHeight, 255, 0);
                playing = !playing;
                counter2++;
            }
        }
        else {
            if (counter2 < 40) {
                if (playing) {
                    CP_Image_DrawAdvanced(logo2, width * 3, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2) - 20, ImageWidth / 2, ImageHeight / 2, 255, 0);
                    playing = !playing;
                    counter2++;
                }
                else {
                    CP_Image_DrawAdvanced(logo2, width * 3, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2) + 20, ImageWidth / 2, ImageHeight / 2, 255, 0);
                    playing = !playing;
                    counter2++;
                }
            }
            else {
                counter3 -= CP_System_GetDt() * (255 / FadeInSeconds);
                alpha = ((int)counter3 % 255);
                CP_Image_DrawAdvanced(logo3, width, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2)-80, 300, 300, alpha, 0);
                CP_Image_DrawAdvanced(logo2, width * 3 + 125, ((CP_System_GetWindowHeight() - ImageHeight / 2) / 2), ImageWidth / 2, ImageHeight / 2, alpha, 0);

                if (counter3 < 0) {
                    CP_Engine_SetNextGameState(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
                }

            }
        }

    }
    else {
        counter += CP_System_GetDt() * (255 / FadeInSeconds);
        alpha = ((int)counter % 255);
        CP_Image_DrawAdvanced(logo, width, (CP_System_GetWindowHeight() - ImageHeight) / 2, ImageWidth, ImageHeight, alpha, 0);
    }




}

void splashscreen_exit(void) {
    CP_Settings_ImageMode(CP_POSITION_CENTER);
    CP_Image_Free(&logo);
}

void Seizure() {

}