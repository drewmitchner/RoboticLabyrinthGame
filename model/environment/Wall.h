#pragma once

#include <vector>
using namespace std;

class Wall
{
private:

	
	double m_height{ 0.01 }; // >> [m]
	double m_width{ 0.01 }; // >> [m]

public:
	Wall()
	{

	}

	Wall(double x1, double y1, double x2, double y2)
		: m_xCoords{ x1, x2 }, m_yCoords{ y1, y2 }
	{

	}

	double Get_Distance(double xBall, double yBall);
	double Get_Width() { return m_width; }

	vector<double> m_xCoords; // size 2 >> [m]
	vector<double> m_yCoords; // size 2 >> [m]
};
