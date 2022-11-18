#include "slider.h"
#include "cprocessing.h"
#include "utils.h"

void slider_init(void) {

	CP_Settings_RectMode(CP_POSITION_CENTER);

    // Set the window size to a sqaure 1000 x 800
    CP_System_SetWindowSize(1000, 800);

	mslider[0].sliderWidth = 700;
	mslider[0].sliderHeight = 50;
	mslider[0].sliderX = 400;
	mslider[0].sliderY = 100;
	mslider[0].sliderKnobRadius = 50;
	mslider[0].sliderKnobY = mslider[0].sliderY;
	mslider[0].sliderKnobX = 700;
	drawSliders(&mslider[0]);


}
void slider_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(122, 122, 122, 255));
	CP_Graphics_DrawRect(900, 400, 200, 800);
	drawSliders(&mslider[0]);
	moveKnob(&mslider[0]);
}
void slider_exit(void) {

}

void drawKnobs(Slider* slide) {
	CP_Settings_Fill(CP_Color_Create(75, 150, 75, 255));
	CP_Graphics_DrawCircle(slide->sliderKnobX, slide->sliderKnobY, slide->sliderKnobRadius * 2);
}

void drawSliders(Slider* slide) {
	CP_Settings_Fill(CP_Color_Create(0, 150, 75, 255));
	CP_Graphics_DrawRect(slide->sliderX, slide->sliderY,slide->sliderWidth,slide->sliderHeight);
	drawKnobs(slide);
}


void moveKnob() {

	Slider* curSlider;

	if (IsCircleClicked(mslider[0].sliderKnobX, mslider[0].sliderKnobY, mslider[0].sliderKnobRadius * 2,CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {

		}
		
	}
}