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

//sets situation where screen starts fully covered 
void setSpriteExtended(void);

//sets situation where screen starts uncovered 
void setSpriteReseted(void);

//animates the sprite into the render, assumes sprite starts at 0-sprite width
int animateIn(void );

//animates the sprite out of render, assumes sprite starts at 0-sprite width
int animateOut(void );

//implement level entry into new level animation, returns 0 when the animation is complete, returns 1 when animation is still running
int initLevelTransition(void );

//typedef for a transit script
typedef void transitScript(void);

//implement level animation, returns 0 when the animation is complete, returns 1 when animation is still running
//Also runs void function transitScript to run on exit level items
int exitLevelTransition(int isAnimationComplete);