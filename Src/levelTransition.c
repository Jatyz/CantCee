#include "cprocessing.h"
#include "levelTransition.h"
#define ANIMATION_LENGTH 1	//length of the animation, in seconds


//remeber to free!!
static void initImage(void) 
{
	lvlTransitImage = CP_Image_Load(TRANSITION_IMAGE_PATH);
}

static void freeImage(void)
{
	if (lvlTransitImage != NULL)
	{
		CP_Image_Free(lvlTransitImage);
	}
}

void setSpriteExtended(void) 
{
	imageXpos = 0;
	CP_Graphics_DrawRect
	(imageXpos + TRANSITION_IMAGE_WIDTH - 10, 0,
		CP_System_GetWindowWidth() - (imageXpos - TRANSITION_IMAGE_WIDTH), CP_System_GetWindowHeight());
}

void setSpriteReseted(void)
{
	imageXpos = 0 - TRANSITION_IMAGE_WIDTH;
}

int animateIn()
{	//animate till sprite is out of screen
	if (imageXpos < CP_System_GetWindowWidth() + CP_Image_GetWidth(lvlTransitImage))
	{	//update the xpostion of the the sprite
		imageXpos += (ANIMATION_LENGTH*(CP_System_GetWindowWidth()+TRANSITION_IMAGE_WIDTH)) * CP_System_GetDt();
		return ANIMATION_NOT_DONE;	//not done animating
	}
	return ANIMATION_DONE;
}

int initLevelTransition()
{
	if (lvlTransitImage == NULL)
	{
		initImage();
	}
	//logics
	CP_Settings_ImageMode(CP_POSITION_CORNER);

	//renders
	CP_Graphics_DrawRect
	(imageXpos + TRANSITION_IMAGE_WIDTH-10, 0,
		CP_System_GetWindowWidth() - (imageXpos - TRANSITION_IMAGE_WIDTH), CP_System_GetWindowHeight());

	int a = CP_Image_GetWidth(lvlTransitImage);
	CP_Image_DrawAdvanced(
		lvlTransitImage,
		imageXpos,
		0,
		TRANSITION_IMAGE_WIDTH,
		TRANSITION_IMAGE_HEIGHT,
		255,
		180);
	//update logic for next frame and return if the animation is done
	return animateOut();
}

int animateOut() 
{
	if (imageXpos < CP_System_GetWindowWidth())
	{
		imageXpos += (ANIMATION_LENGTH * (CP_System_GetWindowWidth() + TRANSITION_IMAGE_WIDTH)) * CP_System_GetDt();
		return ANIMATION_NOT_DONE;	//not done animating
	}
	return ANIMATION_DONE;
}

typedef void transitScript(void);

int exitLevelTransition(int isAnimationComplete, void transitScript(void))
{

	if (lvlTransitImage == NULL)
	{
		initImage();
	}
	//logics
	CP_Settings_ImageMode(CP_POSITION_CORNER);

	//renders
	CP_Graphics_DrawRect
	(0, 0, imageXpos+10, CP_System_GetWindowHeight());

	CP_Image_Draw(
		lvlTransitImage,
		imageXpos,
		0,
		TRANSITION_IMAGE_WIDTH,
		TRANSITION_IMAGE_HEIGHT,
		255);

	if (!isAnimationComplete) {
		transitScript();	//transit to next scene
		freeImage();		//free the image, re init when in new scene
		return ANIMATION_DONE;
	}
	//update logic for next frame and return if the animation is done
	return	animateOut();
}