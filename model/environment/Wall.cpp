#include <iostream>
#include <vector>
#include <cmath>

#include "Wall.h"


double Wall::Get_Distance(double xBall, double yBall)
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
		dx = xBall - x1;
		dy = yBall - y1;
		return sqrt(dx * dx + dy * dy);
	}
	
	// Find the t that minimizes distance
	double t = ((xBall - x1) * dx + (yBall - y1) * dy) /
		(dx * dx + dy * dy);

	if (t < 0)
	{
		// Point 1 is closest
		dx = xBall - x1;
		dy = yBall - y1;
	}
	else if (t > 1)
	{
		// Point 2 is closest
		dx = xBall - x2;
		dy = yBall - y2;
	}
	else
	{
		// Closest is between the two
		dx = xBall - (x1 + t * dx);
		dy = yBall - (y1 + t * dy);
	}

	return sqrt(dx * dx + dy * dy);
}
