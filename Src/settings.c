#include "cprocessing.h"
#include "utils.h"
#include <math.h>

#include "mainMenu.h"
#include "play.h"
#include "howToPlay.h"
#include "settings.h"

/// -------------------------------------
///	Sound settings Code Section
/// -------------------------------------
/// WIP: currently modifies volume on a linear modification scale equivalent to slider pecentage
///		, however, in real life, volume is exponentially softer the lower the decible(db), thus slider should actually
///		 really modify the sound scale with a logarithmic curve equivalent to slider pecentage instead.
///		Why is it not? because log scales are alot of maths :P. it will be low on the piority list
/// 
/// Master volume group sets the maximum limit for both other sound groups
/// 

//declared individually for VS2022 tool tip comments
static float sliderMinX = 150;						//sliders' left most position
static float sliderMaxX = windowWidth - 150;		//sliders' right most position
static float sliderBaseRadius = 15.0f;				//the radius of the small rectangular shape under the slider button 
static float sliderButtonRadius = 30.0f;			//the radius of the slider's button
static float sliderButtonOffsets = 100.0f;			//the distance the sliders should be from each other in pixels
static float topSliderYPos = windowWidth / 2;		//set the first rendered slider to draw at mid screen in y axis

//structure to store required values for each soundgroup slider
struct Slider
{
	float currentVolume;	//currently set volume of the group, is max volume of other groups if is master volume, values between 1.0 and 0.0
	float xButtonPosition;	//the slider button's x position
	float yPosition;		//the y axis position of all elements of the slider
	CP_SOUND_GROUP soundGroup;		//the sound group of the current slider, CP_SOUND_GROUP_MAX if is master volume

} volumeSliders[3];	//for SFX,BGM, and master volume respectively, master volume sound group should never be assigned as a sound group

//convenient defines to denote which array item belongs to which sound group
#define SFX CP_SOUND_GROUP_SFX	
#define BGM CP_SOUND_GROUP_MUSIC
#define VOLMASTER 2

//forcibly get an X value that is within slider width
float getWithinSliderValue(float const Xpos)
{
	if (Xpos > sliderMaxX)
	{	//force to max if value is above max
		return sliderMaxX;
	}
	if (Xpos < sliderMinX)
	{	//force to min if value under min
		return sliderMinX;
	}
	return Xpos;	//return original value if value is acceptable
}

float convertSliderValueToVolume(float const Xpos)
{
	if (Xpos > sliderMaxX)
	{	//force to max if value is above max
		return 1.0f;	//return comverted equivalent
	}
	if (Xpos < sliderMinX)
	{	//force to min if value under min
		return 0.0f;	//return comverted equivalent
	}
	return (Xpos-sliderMinX)/(sliderMaxX-sliderMinX);	//return original value in terms of pecent of slider moved right if value is acceptable
}

float convertVolumeToSliderValue(float const Xpos)
{
	if (Xpos > 1.0)
	{	//force to max if value is above max
		return sliderMaxX;	//return comverted equivalent
	}
	if (Xpos < 0.0)
	{	//force to min if value under min
		return sliderMinX;	//return comverted equivalent
	}
	return Xpos * (sliderMaxX - sliderMinX) + sliderMinX ;	//return original value converted if value is acceptable
}

//draws the slider range (call before calling drawSliderButton())
void drawSliderbase(float const Ypos)
{
	CP_Settings_RectMode(CP_POSITION_CENTER);	//set the graphics draw mode to center
	
	//set a fill color and no stroke 
	CP_Settings_Fill(CP_Color_Create(50, 50, 50, 255));
	CP_Settings_NoStroke();

	//draw the small slider rectangle that is supposed to be under the slider button
	CP_Graphics_DrawCircle(sliderMinX, Ypos, sliderBaseRadius * 2);
	CP_Graphics_DrawCircle(sliderMaxX, Ypos, sliderBaseRadius * 2);
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Graphics_DrawRect(sliderMinX, Ypos - sliderBaseRadius, sliderMaxX - sliderMinX, sliderBaseRadius * 2);

	//reset the stroke to prevent further no strokes
	CP_Settings_Stroke(CP_Color_Create(0,0,0,255));
}

//draws the slider Button 
double drawSliderButton(float const XPos, float const Ypos)
{	//set a fill color and no stroke 
	CP_Settings_Fill(CP_Color_Create(150, 150, 150, 255));
	CP_Settings_NoStroke();
	float newXPos = getWithinSliderValue(XPos);	//get a forcibly set x axis position within the slider value

	CP_Settings_RectMode(CP_POSITION_CENTER);	//draw the slider using the center position
	CP_Graphics_DrawCircle(newXPos, Ypos, sliderButtonRadius * 2);	//draw the slider button
	CP_Settings_RectMode(CP_POSITION_CORNER);	//return draw mode to default mode
	
	//reset the stroke to prevent further no strokes
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	//returns the percentage right the slider is to the maximum distance it has to cover
	return (XPos - sliderMinX) / (sliderMaxX - sliderMinX);
}

//set all other volume groups expected to be used to a set volume
void handleVolumeMaster(float const volume)
{	//new volume variable to store a value within 0.0 and 1.0;
	float newVol = (volume > 1.0f) ? 1.0f : volume;
	newVol = (volume < 0.0f) ? 0.0f : volume;
	//set master volume's current volume
	volumeSliders[VOLMASTER].currentVolume = newVol;

	//find if sfx and bgm is currently larger than the master volume, if so, make their volume equal to the master volume
	volumeSliders[SFX].currentVolume = (newVol < volumeSliders[SFX].currentVolume) ? newVol : volumeSliders[SFX].currentVolume;
	volumeSliders[BGM].currentVolume = (newVol < volumeSliders[BGM].currentVolume) ? newVol : volumeSliders[BGM].currentVolume;
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_SFX, volumeSliders[SFX].currentVolume);		//set volume of group SFX, volume is between 1.0 and 0.0
	CP_Sound_SetGroupVolume(CP_SOUND_GROUP_MUSIC, volumeSliders[BGM].currentVolume);	//set volume of group BGM, volume is between 1.0 and 0.0

	//get x axis position equivalent to volume percentage
	newVol *= (sliderMaxX - sliderMinX);
	newVol += sliderMinX;

	//set master current slider button's x position to the new X axis equivalent of volume percentage 
	volumeSliders[VOLMASTER].xButtonPosition = newVol;

	//update slider information
	volumeSliders[SFX].xButtonPosition = convertVolumeToSliderValue(volumeSliders[SFX].currentVolume);
	volumeSliders[BGM].xButtonPosition = convertVolumeToSliderValue(volumeSliders[BGM].currentVolume);
}

//mutes all assumed used sound groups
void muteAll(void)	//makes volume of master volume to 0
{
	handleVolumeMaster(0.0f);
}

//initialize all volume levels to max, ignore all previous settings
void intiVolume(void)
{	//set all volume level to max
	volumeSliders[VOLMASTER].currentVolume = convertSliderValueToVolume(sliderMaxX);
	volumeSliders[SFX].currentVolume = convertSliderValueToVolume(sliderMaxX);
	volumeSliders[BGM].currentVolume = convertSliderValueToVolume(sliderMaxX);

	//set all sliders to max volume
	volumeSliders[VOLMASTER].xButtonPosition = sliderMaxX;
	volumeSliders[SFX].xButtonPosition = sliderMaxX;
	volumeSliders[BGM].xButtonPosition = sliderMaxX;	

	//set the y axis position of each slider
	volumeSliders[VOLMASTER].yPosition = topSliderYPos;
	volumeSliders[SFX].yPosition = volumeSliders[VOLMASTER].yPosition + sliderButtonOffsets;
	volumeSliders[BGM].yPosition = volumeSliders[SFX].yPosition + sliderButtonOffsets;

	//set appropriate sound groups to each slider
	volumeSliders[VOLMASTER].soundGroup = CP_SOUND_GROUP_MAX;
	volumeSliders[SFX].soundGroup = CP_SOUND_GROUP_SFX;
	volumeSliders[BGM].soundGroup = CP_SOUND_GROUP_MUSIC;
	
	handleVolumeMaster(1.0f);	//set all volume to maximum value
}

//draws all sliders
void drawAllSliders(void) 
{	//draw slider base range
	drawSliderbase(volumeSliders[VOLMASTER].yPosition);
	drawSliderbase(volumeSliders[SFX].yPosition);
	drawSliderbase(volumeSliders[BGM].yPosition);

	//draw slider's button
	drawSliderButton(volumeSliders[VOLMASTER].xButtonPosition, volumeSliders[VOLMASTER].yPosition);
	drawSliderButton(volumeSliders[SFX].xButtonPosition, volumeSliders[SFX].yPosition);
	drawSliderButton(volumeSliders[BGM].xButtonPosition, volumeSliders[BGM].yPosition);
}

//handles all slider and volume interaction, all without params too :), When sounds implemented, check with sounds as well. Thanks Danish \('<
void handleSliderInteraction(void)
{	
	//first set position of all slider position to current value of volume stored in volume array
	volumeSliders[VOLMASTER].xButtonPosition = convertVolumeToSliderValue(volumeSliders[VOLMASTER].currentVolume);
	volumeSliders[SFX].xButtonPosition = convertVolumeToSliderValue(volumeSliders[SFX].currentVolume);
	volumeSliders[BGM].xButtonPosition = convertVolumeToSliderValue(volumeSliders[BGM].currentVolume);

	//go backwards through sliders array, as master volume is last element
	for (int i = (sizeof(volumeSliders) / sizeof(volumeSliders[0]) - 1);
		i > -1;
		i--)	
	{	//if slider area is hovered
		if (IsAreaClicked(
			(sliderMaxX - sliderMinX)/2 + sliderMinX,
			volumeSliders[i].yPosition,
			(sliderMaxX - sliderMinX),
			sliderButtonRadius * 2,
			CP_Input_GetMouseX(),
			CP_Input_GetMouseY()))
		{	
			//if hovered area is clicked or held
			if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT))
			{	//manipulate the slider position to the mouse x position
				volumeSliders[i].xButtonPosition = getWithinSliderValue(CP_Input_GetMouseX());
			}
			//if release left mouse button, update volume levels in array
			if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
			{	
				if (volumeSliders[i].soundGroup == CP_SOUND_GROUP_MAX)	//special case for master volume
				{
					handleVolumeMaster(convertSliderValueToVolume(CP_Input_GetMouseX()));	//update master volume
					break;
				}
				//if slider's settings are within the master volume settings
				if (getWithinSliderValue(CP_Input_GetMouseX()) <= volumeSliders[VOLMASTER].xButtonPosition) 
				{	//set sound group volume to slider equivalent
					CP_Sound_SetGroupVolume(
						volumeSliders[i].soundGroup,
						convertSliderValueToVolume(CP_Input_GetMouseX()));
					//update button position
					volumeSliders[i].xButtonPosition = getWithinSliderValue(CP_Input_GetMouseX());
					//update volume info
					volumeSliders[i].currentVolume = convertSliderValueToVolume(CP_Input_GetMouseX());
				}
				else 
				{	//set sound group volume to slider equivalent of master volume's volume
					CP_Sound_SetGroupVolume(
						volumeSliders[i].soundGroup,
						volumeSliders[VOLMASTER].currentVolume);
					//update button position to slider equivalent of master volume's button position
					volumeSliders[i].xButtonPosition = volumeSliders[VOLMASTER].xButtonPosition;
					//update volume info to slider equivalent of master volume's current volume
					volumeSliders[i].currentVolume = volumeSliders[VOLMASTER].currentVolume;
				}
			}
		}
	}
}

/// -------------------------------------
///	End of Sound settings Code Section
/// -------------------------------------






//load
// art assets
void settings_Init()
{	
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));//background, change if needed
	intiVolume();	//initialize volume
}



void settings_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	handleSliderInteraction();
	drawAllSliders();
}

// draw

//free memory

// unload
void settings_Exit()
{

}








