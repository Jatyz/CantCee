#pragma once

#ifndef TRANSITION_IMAGE_PATH
#define TRANSITION_IMAGE_PATH "./Assets/LevelTransitionSprite.png"
#define TRANSITION_IMAGE_WIDTH 230
#define TRANSITION_IMAGE_HEIGHT 800
#endif // !IMAGE_PROPERTIES

extern enum
{
	ANIMATION_DONE = 0,
	ANIMATION_NOT_DONE = 1
};

static CP_Image lvlTransitImage;
static double imageXpos = -230;;

void setSpriteExtended(void);

void setSpriteReseted(void);

int animateIn(void );

int initLevelTransition(void );

int animateOut(void );

typedef void transitScript(void);

int exitLevelTransition(int isAnimationComplete, void transitScript(void));