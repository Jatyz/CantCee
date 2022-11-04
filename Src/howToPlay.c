#include "cprocessing.h"
#include "utils.h"

#include "mainMenu.h"
#include "play.h"
#include "settings.h"



void howToPlay_Init()
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

void howToPlay_Update()
{
    CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 0));
	// How To Play Text
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("How To Play", (windowWidth / 2.0f), (windowHeight / 2.0f - 350));

	// Placeholder W
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(windowWidth / 2.0f - 100, (windowHeight / 2.0f - 100), buttonWidth, buttonHeight);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("W", windowWidth / 2.0f - 100, (windowHeight / 2.0f) - 100);
    
    // Placeholder A
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(windowWidth / 2.0f - 200, (windowHeight / 2.0f + 100), buttonWidth, buttonHeight);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("A", windowWidth / 2.0f - 200, (windowHeight / 2.0f) + 100);

    // Placeholder S
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(windowWidth / 2.0f - 100, (windowHeight / 2.0f + 100), buttonWidth, buttonHeight);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("S", windowWidth / 2.0f - 100, (windowHeight / 2.0f) + 100);

    // Placeholder D
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(windowWidth / 2.0f, (windowHeight / 2.0f + 100), buttonWidth, buttonHeight);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("D", windowWidth / 2.0f, (windowHeight / 2.0f) + 100);


}

void howToPlay_Exit()
{

}
