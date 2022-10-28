#include "cprocessing.h"
#include "math.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	// TOD
	
	float x_max = area_center_x + (area_width / 2);					// max X of area clicked
	float x_min = area_center_x - (area_width / 2);
	float y_max = area_center_y + (area_height / 2);					// max y of area clicked
	float y_min = area_center_y - (area_height / 2);

	if (click_x >= x_min && click_x <= x_max && click_y >= y_min && click_y <= y_max)
	{
		return 1;
	}
	return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	// TODO
	float distX = click_x - circle_center_x;
	float distY = click_y - circle_center_y;
	
	float originToPoint = sqrt((distX * distX) + (distY * distY));

	if (originToPoint <= (diameter / 2))
	{
		return 1;
	}
	return 0;
}

CP_Vector AngleToVector(float radian_angle)
{
    // TODO 
    CP_Vector point;
	point = CP_Vector_Set(cos(radian_angle), sin(radian_angle));

    return point;
}