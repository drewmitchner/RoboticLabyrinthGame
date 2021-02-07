#include <iostream>
#include <vector>

#include "..\environment\Board.h"
#include "Sim_Episode.h"

#include "../../gnc/exec/GNC_Exec.h"
#include "../../gnc/control/GNC_Control.h"

extern Sim_Episode episode;

extern Board board;

extern Gnc_Exec exec;

extern Gnc_Control control;

void Sim_Episode::Setup_Episode(int type, double dt, double timeout, bool logging)
{
	switch (type)
	{
	case 1:
		// Model Restart
		board.Restart(0.0, 0.0);

		// GNC Restart
		exec.Restart();

		episode.dt = dt;
		episode.time = 0.0;
		episode.timeout = timeout;
		episode.logging = logging;
		
		break;
	default:
		break;
	}

	if (episode.logging)
	{
		// Log initial conditions
	}

	episode.status = Status::running;
}

void Sim_Episode::Run_Episode()
{
	while (episode.status != Status::ended)
	{
		board.Print_Pos();
		// Camera measurement
		// State estimate
		// Guidance
		// Control
		// Servo Output

		exec.Update();

		// Actuator update
		// Environment update
		board.Compute_Rates_Of_Change(control.theta_dot_cmd, control.phi_dot_cmd);
		board.Apply_Euler_Integration(episode.dt, control.theta_dot_cmd, control.phi_dot_cmd);

		// Step episode timer
		episode.time += episode.dt;

		if (episode.logging)
		{
			// Log this timestep
		}

		if (board.Check_Termination() != Terminal::continue_run ||
			episode.time >= episode.timeout)
		{
			episode.status = Status::ended;
		}
	}
	
	
}

void Sim_Episode::Finish_Episode()
{
	std::cout << "\nEpisode ended at (" << board.GetXp() << ", " << board.GetYp() << ")";
	std::cout << " due to\n";

	switch (board.Check_Termination())
	{
	case Terminal::reached_goal:
		std::cout << "Goal Reached\n";
		break;
	case Terminal::wall_collision:
		std::cout << "Wall Collision\n";
		break;
	case Terminal::hole_collision:
		std::cout << "Hole Collision\n";
		break;
	default:
		std::cout << "Episode Timeout\n";
		break;
	}

	if (episode.logging)
	{
		// Log terminal conditions
	}
}
