#include "cprocessing.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "level7.h"
#include "level8.h"
#include "level9.h"
#include "level10.h"
#include "level11.h"
#include "level12.h"
#include "level13.h"
#include "level14.h"
#include "level15.h"
#include "play.h"
#include "levelselect.h"
#include "mainmenu.h"
#include "levelTransition.h"
#include "game.h"

//set exit transition for all scenes and then change scene

void startLevel1(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level1_init, level1_update, level1_exit);

}

void startLevel2(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level2_init, level2_update, level2_exit);


}

void startLevel3(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level3_init, level3_update, level3_exit);

}

void startLevel4(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level4_init, level4_update, level4_exit);
}

void startLevel5(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level5_init, level5_update, level5_exit);
}


void startLevel6(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level6_init, level6_update, level6_exit);
}

void startLevel7(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level7_init, level7_update, level7_exit);
}

void startLevel8(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level8_init, level8_update, level8_exit);
}

void startLevel9(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level9_init, level9_update, level9_exit);
}

void startLevel10(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level10_init, level10_update, level10_exit);
}

void startLevel11(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level11_init, level11_update, level11_exit);
}

void startLevel12(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level12_init, level12_update, level12_exit);
}

void startLevel13(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level13_init, level13_update, level13_exit);
}

void startLevel14(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level14_init, level14_update, level14_exit);
}

void startLevel15(void)
{
	transitLevel();
	CP_Engine_SetNextGameStateForced(level15_init, level15_update, level15_exit);
}

void transitLevel(void)
{
	//set level exited
	levelExited = 1;

	if (levelExited)	//when level exit, 
	{	//render exit level transition animation
		levelExited = exitLevelTransition(levelExited);	//second parameter runs when the animation is complete, returns 0 when animation is done
		if (!levelExited) {
			//finish exit level
			levelExited = 0;
		}		
	}
}


void startLevelSelect(void) {
	CP_Engine_SetNextGameStateForced(play_Init, play_Update, play_Exit);
}



