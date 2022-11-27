//---------------------------------------------------------
// file:	utils.c
// author:	Ong You Yang
// email:	youyang.o@digipen.edu
//
// brief:	mouse functions
//			
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2022 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "math.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// TOD
	
	float x_max = area_center_x + (area_width / 2);				// max X of area clicked
	float x_min = area_center_x - (area_width / 2);
	float y_max = area_center_y + (area_height / 2);					// max y of area clicked
	float y_min = area_center_y - (area_height / 2);

	if (click_x >= x_min && click_x <= x_max && click_y >= y_min && click_y <= y_max)
	{
		return 1;
	}
	return 0;
}
