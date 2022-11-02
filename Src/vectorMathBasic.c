#define _USE_MATH_DEFINES

#include <math.h>



double distanceOfVectorR2(
	double const vectorX,
	double const vectorY
) 
{
	return sqrt((vectorX*vectorX)+(vectorY*vectorY));
}

double dotProductR2
(
	double const vector1X,
	double const vector1Y,
	double const vector2X,
	double const vector2Y
) 
{
	return ((vector1X * vector2X) + (vector1Y * vector2Y));
}

//find and return angle between vectors in radians
double angleBetweenVectorsR2
(
	double const X1,
	double const Y1,
	double const X2,
	double const Y2
)
{
	return 
		acos(
			dotProductR2(X1, Y1, X2, Y2) / (distanceOfVectorR2(X1, Y1) * distanceOfVectorR2(X2, Y2))
		);
}

//find and return angle between vectors in radians
double angleBetweenVectorsDegreesR2
(
	double const X1,
	double const Y1,
	double const X2,
	double const Y2
)
{
	double z = ((acos(dotProductR2(X1, Y1, X2, Y2) / (distanceOfVectorR2(X1, Y1) * distanceOfVectorR2(X2, Y2)))) * (180 / M_PI));
	return acos(dotProductR2(X1, Y1, X2, Y2) / (distanceOfVectorR2(X1, Y1) * distanceOfVectorR2(X2, Y2)))*(180/M_PI);
}

//find angle of point from origin, in degrees
double angleOfPointR2
(
	double const X1,
	double const Y1
) 
{
	if (X1 == 0)	//catch domain errors
	{
		if (Y1 > 0) 
		{return 90;}
		if (Y1 < 0)
		{return 270;}
		if (Y1 == 0)
		{return 0;}
	}
	double ret = atan2(Y1,X1)*(180/M_PI);
	if (ret < 0) //ret negative
	{
		return (double)360 + ret;
	}
	else		//ret positive
	{
		return ret;
	}
}