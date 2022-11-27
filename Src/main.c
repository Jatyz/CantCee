//---------------------------------------------------------
// file:	main.c
// author:	Jarran Tan Yan Zhi
// email:	jarranyanzhi.tan@digipen.edu
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "splashscreen.h"

int main(void)
{
	CP_Engine_SetNextGameState(splashscreen_init, splashscreen_update, splashscreen_exit);

	CP_Engine_Run();
	return 0;
}
