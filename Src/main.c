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
#include "main.h"
#include "grid.h"
#include "game.h"

int main(void)
{

	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	//CP_Engine_SetNextGameState(mainMenu_Init, mainMenu_Update, mainMenu_Exit);
	//CP_Engine_SetNextGameState(play_Init, play_Update, play_Exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
  
	CP_Engine_Run();
	return 0;
}
