#include <iostream>
#include <vector>

#include "..\environment\Board.h"
#include "Sim_Episode.h"

extern Sim_Episode episode;

extern Board board;

void Sim_Episode::Setup_Episode(int type, double dt, double timeout, bool logging)
{
	switch (type)
	{
	case 1:
		board.Reset(0.0, 0.0);

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
		// Camera measurement
		// State estimate
		// Guidance
		// Control
		// Servo Output

		// Actuator update
		// Environment update
		board.Compute_Rates_Of_Change(3.14/20.0, 0.0);
		board.Apply_Euler_Integration(episode.dt, 3.14 / 20.0, 0.0);

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
