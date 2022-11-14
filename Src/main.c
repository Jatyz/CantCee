//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
//#include "splashscreen.h"
#include "mainmenu.h"
#include "play.h"
#include "credits1.h"
#include "howToPlay.h"
#include "main.h"
#include "grid.h"
#include "game.h"
#include "level1.h"
#include "level5.h"
#include "level8.h"
#include "level9.h"
#include "level15.h"
#include "level14.h"
#include "level10.h"

int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
	//CP_Engine_SetNextGameState(credits1_Init, credits1_Update, credits1_Exit);
	//CP_Engine_SetNextGameState(play_Init, play_Update, play_Exit);
	//CP_Engine_SetNextGameState(level8_init, level8_update, level8_exit);
	//CP_Engine_SetNextGameState(level1_init, level1_update, level1_exit);
	//CP_Engine_SetNextGameState(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
	////CP_Engine_SetNextGameState(play_Init, play_Update, play_Exit);
	//CP_Engine_SetNextGameState(level15_init, level15_update, level15_exit);
	CP_Engine_SetNextGameState(level14_init, level14_update, level14_exit);
	//(level10_init, level10_update, level10_exit);

	//CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	//CP_Engine_SetNextGameState(howToPlay_Init, howToPlay_Update, howToPlay_Exit);
  

	//CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	//CP_Engine_SetNextGameStateForced(level9_init, level9_update, level9_exit);

	CP_Engine_Run();
	return 0;
}
