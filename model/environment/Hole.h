#pragma once

#include <vector>
#include <cmath>

using namespace std;

class Hole
{
private:

public:
	double m_x{ -0.1 }; // Location in frame P >> [m]
	double m_y{ 0.0 }; // >> [m]

	double m_radius{ 0.013/2.0 }; // [m]

	double Get_Distance(double xBall, double yBall)
	{
		return sqrt(pow(m_x - xBall, 2) + pow(m_y - yBall, 2));
	}

};
