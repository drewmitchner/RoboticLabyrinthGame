#pragma once

#include <vector>
using namespace std;

class Ball
{
private:

public:
	double m_xp{ 0.0 }; // Position in frame P >> [m]
	double m_yp{ 0.0 }; // >> [m]
	double m_vxp{ 0.0 }; // Velocity in frame P >> [m/s]
	double m_vyp{ 0.0 };

	double m_vxp_dot{ 0.0 };
	double m_vyp_dot{ 0.0 };

	double m_mass{ 0.0083 }; // [kg]
	double m_radius{ 0.0127 / 2.0 }; // >> [m]

	Ball()
	{

	}

	Ball(double x_init, double y_init, double vx_init, double vy_init)
		: m_xp{x_init}, m_yp{ y_init }, m_vxp{ vx_init }, m_vyp{ vy_init }
	{

	}

};
