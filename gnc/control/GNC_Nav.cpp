// GNC_Nav.cpp
// Handles state estimate
// Interfaces with camera, utilizes EKF for state estimate

#include "GNC_Nav.h"
#include "GNC_Control.h"
#include "../../model/environment/Board.h"

//*************** OBJECT COLLABORATION ***************

extern Board board;

extern Gnc_Control control;

//*************** OBJECT DEFINITION ***************

Gnc_Nav nav;

void Gnc_Nav::Init(double T_update)
{
	dt = T_update;

	mode = Nav_Mode::PASS_THROUGH;
}

void Gnc_Nav::Restart()
{
	

	mode = Nav_Mode::PASS_THROUGH;

	if (mode == Nav_Mode::PASS_THROUGH)
	{
		// board.cpp must be Restart()'ed before this
		xp = board.GetXp();
		yp = board.GetYp();
		vxp = board.GetVxp();
		vyp = board.GetVyp();

		theta = 0.0;
		phi = 0.0;
		theta_dot = 0.0;
		phi_dot = 0.0;
	}
}

void Gnc_Nav::Update()
{
	if (mode == Nav_Mode::PASS_THROUGH)
	{
		xp = board.GetXp();
		yp = board.GetYp();
		vxp = board.GetVxp();
		vyp = board.GetVyp();

		theta = control.theta;
		phi = control.phi;
		theta_dot = control.theta_dot_cmd;
		phi_dot = control.phi_dot_cmd;
	}
}
