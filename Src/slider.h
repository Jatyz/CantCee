#pragma once

void slider_init(void);
void slider_update(void);
void slider_exit(void);

typedef struct SLIDER {
	float sliderWidth;
	float sliderHeight;
	float sliderX;
	float sliderY;
	float sliderKnobRadius;
	float sliderKnobX;
	float sliderKnobY;
	float max;
}Slider;

Slider mslider[3];

void drawSliders(Slider* slide);
void moveKnob(Slider* slide);