#pragma once

#include <iostream>
#include <vector>

using namespace std;

enum class Nav_Mode
{
	PASS_THROUGH,
	EKF,
	CAMERA
};

class Gnc_Nav
{
private:

public:
	double dt{ 0.01 }; // Time in between updates [sec]

	// State
	double xp{ 0.0 }; // X-position estimate [m]
	double yp{ 0.0 }; // Y-position estimate [m]
	double vxp{ 0.0 }; // X-velocity estimate [m/sec]
	double vyp{ 0.0 }; // Y-Velocity estimate [m/sec]

	double theta{ 0.0 }; // Rotation angle about y-axis [rad]
	double phi{ 0.0 }; // Rotation angle about intermediate x-axis [rad]
	double theta_dot{ 0.0 }; // Rotation rate about y-axis [rad/s]
	double phi_dot{ 0.0 }; // Rotation rate about intermediate x-axis [rad/s]

	void Init(double T_update);
	void Restart();
	void Update();

	Nav_Mode mode;
};
