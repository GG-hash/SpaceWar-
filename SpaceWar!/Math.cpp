#include "Math.h"

float FixRadianAngle(float angle)
{
	while (angle <= -M_PI)
	{
		angle += 2.0f * (float)M_PI;
	}
	while (angle > M_PI)
	{
		angle -= 2.0f * (float)M_PI;
	}
	return angle;
}// float FixRadianAngle(float angle)