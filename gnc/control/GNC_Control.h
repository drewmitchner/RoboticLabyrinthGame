#pragma once

#include <iostream>
#include <vector>


using namespace std;

enum class Control_Mode
{
	MANUAL,
	TRACKING
};

class Gnc_Control
{
private:

public:
	// Time
	double dt{ 0.01 }; // Time in between updates [sec]

	// Gains
	double kp_acc{ 0.5 }; // Proportional gain [(rad/sec) / (m/sec)]
	double kd_acc{ 0.5 }; // Derivative gain [(rad/sec) / (m/sec^2)]
	double tau_acc{ 0.05 }; //

	double max_rate_cmd{ 20.0 / 57.3 }; // Max commandable rotation rate [rad/sec]


	// Accels
	double vel_err_x{ 0.0 }; // Error in commanded x-acceleration [m/sec]
	double vel_err_y{ 0.0 }; // Error in commanded y-acceleration [m/sec^2]

	double vel_err_prev_x{ 0.0 }; // Previous error in commanded x-acceleration [m/sec]
	double vel_err_prev_y{ 0.0 }; // Previous error in commanded y-acceleration [m/sec]

	double vel_meas_x{ 0.0 }; // Measured x-accel based on dynamic model [m/sec]
	double vel_meas_y{ 0.0 }; // Measured y-accel based on dynamic model [m/sec]

	// Output
	double theta_dot_cmd{ 0.0 }; // Rotational rate commanded about y-axis [rad/sec]
	double phi_dot_cmd{ 0.0 }; // Rotational rate commanded about intermediate x-axis [rad/sec]

	void Init(double T_update);
	void Restart();
	void Update();

	void Calc_Vel_Err();
	void Calc_Rate_Cmd();
	void Update_Servo_Position();

	// State variables
	double theta{ 0.0 };
	double phi{ 0.0 };
	double theta_dot{ 0.0 };
	double phi_dot{ 0.0 };

	double xp{ 0.0 };
	double yp{ 0.0 };
	double vxp{ 0.0 };
	double vyp{ 0.0 };
};

