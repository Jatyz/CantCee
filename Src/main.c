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
#include "howToPlay1.h"
#include "main.h"
#include "grid.h"
#include "game.h"
#include "level1.h"
#include "level3.h"
#include "level5.h"
#include "level8.h"
#include "level9.h"
#include "level15.h"
#include "level14.h"
#include "level10.h"

int main(void)
{

	CP_Engine_SetNextGameState(mainMenu_Init, mainMenu_Update, mainMenu_Exit);

	CP_Engine_Run();
	return 0;
}
