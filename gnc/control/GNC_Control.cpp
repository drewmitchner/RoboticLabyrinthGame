// GNC_Control.cpp
// Low-level controller
// Takes in velocity commands from GNC_Guid.cpp, closes the loop to output rotation rate commands

#include<iostream>
#include<vector>

#include "GNC_Control.h"
#include "GNC_Nav.h"
#include "GNC_Guid.h"

// Utils
#include "../util/GNC_Inline.h"

//*************** OBJECT COLLABORATION ***************

extern Gnc_Nav nav;

extern Gnc_Guid guid;

//*************** OBJECT DEFINITION ***************

Gnc_Control control;

void Gnc_Control::Init(double T_update)
{
	dt = T_update;
}

void Gnc_Control::Restart()
{
	

	// Reset variables
	vel_err_x = 0.0;
	vel_err_y = 0.0;

	vel_err_prev_x = 0.0;
	vel_err_prev_y = 0.0;

	theta_dot_cmd = 0.0;
	phi_dot_cmd = 0.0;

	xp = 0.0;
	yp = 0.0;
	vxp = 0.0;
	vyp = 0.0;

	theta = 0.0;
	phi = 0.0;
}

void Gnc_Control::Update()
{
	// Update state from Nav
	xp = nav.xp;
	yp = nav.yp;
	vxp = nav.vxp;
	vyp = nav.vyp;

	// Execute feedback loop
	Calc_Vel_Err();

	Calc_Rate_Cmd();
}

void Gnc_Control::Calc_Vel_Err()
{
	vel_err_x = guid.vel_cmd_x - vxp;
	vel_err_y = guid.vel_cmd_y - vyp;
	//std::cout << "vel_cmd_x: " << guid.vel_cmd_x << '\n';
	//std::cout << "vxp: " << vxp << '\n';
	//std::cout << "vel_err_x " << vel_err_x << '\n';
}

void Gnc_Control::Calc_Rate_Cmd()
{
	// Positive theta causes positive x-movement
	// Positive phi causes negative y-movement
	theta_dot_cmd =  kp_acc * vel_err_x + kd_acc * (vel_err_x - vel_err_prev_x) / dt;
	phi_dot_cmd   = -kp_acc * vel_err_y - kd_acc * (vel_err_y - vel_err_prev_y) / dt;

	theta_dot_cmd = LIMIT(-max_rate_cmd, theta_dot_cmd, max_rate_cmd);
	phi_dot_cmd   = LIMIT(-max_rate_cmd, phi_dot_cmd,   max_rate_cmd);

	vel_err_prev_x = vel_err_x;
	vel_err_prev_y = vel_err_y;

	//std::cout << "theta_dot_cmd " << theta_dot_cmd * 57.3 << '\n';
}

void Gnc_Control::Update_Servo_Position()
{
	theta += theta_dot_cmd * dt;
	phi   += phi_dot_cmd   * dt;


}
