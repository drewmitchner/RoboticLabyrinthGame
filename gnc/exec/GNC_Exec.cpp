// GNC_Exec.cpp
// Main hub for GNC functions and objects
// Calls each init(), and restart() function. Calls each update() function at the desired Hz

#include<iostream>
#include<vector>

#include "GNC_Exec.h"
#include "../control/GNC_Nav.h"
#include "../control/GNC_Guid.h"
#include "../control/GNC_Control.h"

// Utils
#include "../util/GNC_Inline.h"

//*************** OBJECT COLLABORATION ***************

extern Gnc_Nav nav;

extern Gnc_Guid guid;

extern Gnc_Control control;

//*************** OBJECT DEFINITION ***************

Gnc_Exec exec;

void Gnc_Exec::Init()
{
	exec_mode = Gnc_Mode::STANDBY;

	// Timing setup
	exec_f = 100;
	nav_f = 100;
	guid_f = 100;
	control_f = 100;

	exec_T = 1. / exec_f;
	nav_T = 1. / nav_f;
	guid_T = 1. / guid_f;
	control_T = 1. / control_f;

	nav_n_cycles = exec_f / nav_f;
	guid_n_cycles = exec_f / guid_f;
	control_n_cycles = exec_f / control_f;

	// Initialize GNC Components
	nav.Init(nav_T);
	guid.Init(guid_T);
	control.Init(control_T);
}

void Gnc_Exec::Restart()
{
	exec_mode = Gnc_Mode::NAVIGATE;

	timer = 0.0;
	cycle_counter = 1;

	nav.Restart();
	guid.Restart();
	control.Restart();

}

void Gnc_Exec::Update()
{
	if (cycle_counter % nav_n_cycles == 0)
	{
		nav.Update();
	}

	if (cycle_counter % guid_n_cycles == 0)
	{
		guid.Update();
	}

	if (cycle_counter % control_n_cycles == 0)
	{
		control.Update();
	}

	// End of exec Update()
	timer += exec_T;
	++cycle_counter;
	if (cycle_counter > exec_f)
	{
		cycle_counter = 1; // Reset cycle_counter. Only needs to be as large as exec update rate
	}
}
