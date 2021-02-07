#include <iostream>
#include <vector>
#include <cmath>

#include "Wall.h"


double Wall::Get_Distance(double xBall, double yBall)
{
	double dx{ 0.0 };
	double dy{ 0.0 };

	Wall::Get_Closest_Point(xBall, yBall, dx, dy);

	return sqrt(dx * dx + dy * dy);
}

void Wall::Get_Closest_Point(double xBall, double yBall, double& dx_Out, double& dy_Out)
{
	double x1 = Wall::m_xCoords[0];
	double x2 = Wall::m_xCoords[1];
	double y1 = Wall::m_yCoords[0];
	double y2 = Wall::m_yCoords[1];

	double dx = x2 - x1;
	double dy = y2 - y1;

	if ((dx == 0) && (dy == 0))
	{
		// It's a point, not a line
		dx_Out = xBall - x1;
		dy_Out = yBall - y1;
	}

	// Find the t that minimizes distance
	double t = ((xBall - x1) * dx + (yBall - y1) * dy) /
		(dx * dx + dy * dy);

	if (t < 0)
	{
		// Point 1 is closest
		dx_Out = xBall - x1;
		dy_Out = yBall - y1;
	}
	else if (t > 1)
	{
		// Point 2 is closest
		dx_Out = xBall - x2;
		dy_Out = yBall - y2;
	}
	else
	{
		// Closest is between the two
		dx_Out = xBall - (x1 + t * dx);
		dy_Out = xBall - (y1 + t * dy);
	}
}
