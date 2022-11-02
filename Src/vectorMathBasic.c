
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
	return ((vector1X*vector2X)+(vector1Y*vector2Y));
}

//find and return angle between vectors
double angleBetweenVectorsR2
(
	double const X1,
	double const Y1,
	double const X2,
	double const Y2
)
{
	return 
		(
			acos(
				dotProductR2(X1,Y1,X2,Y2)
				/ (distanceOfVectorR2(X1,Y1)*distanceOfVectorR2(X2,Y2))
			)
		);
}