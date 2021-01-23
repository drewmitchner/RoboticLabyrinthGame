#pragma once

#include <iostream>
#include <vector>

#include "Wall.h"
#include "Hole.h"
#include "Ball.h"

constexpr auto G0 = (9.81);

using namespace std;

enum class Terminal {
	continue_run,
	reached_goal,
	wall_collision,
	hole_collision
};

class Board
{
private:

	double m_xLength{ 0.3 }; // >> [m]
	double m_yLength{ 0.3 }; // >> [m]

	double m_xStart{ -0.15 }; // starting position of the ball >> [m]
	double m_yStart{ 0.15 }; // >> [m]
	double m_xFinish{ 0.15 }; // "Goal" position for the ball >> [m]
	double m_yFinish{ -0.15 }; // >> [m]

	double m_theta{ 0.0 }; // rotation about the y-axis in the  inertial frame >> [rad]
	double m_phi{ 0.0 }; // rotation about intermediate x-axis >> [rad]

	Ball ball;
	vector<Wall> walls; // vector of all the walls
	vector<Hole> holes; // vector of all the holes

public:
	Board()
		: ball{ 0.0, 0.0, 0.0, 0.0 }
	{
		// Create vector of walls

		walls.push_back(Wall( 0.13, 0.13, 0.13,-0.13));
		walls.push_back(Wall( 0.13,-0.13,-0.13,-0.13));
		walls.push_back(Wall(-0.13,-0.13,-0.13, 0.13));
		walls.push_back(Wall(-0.13, 0.13, 0.13, 0.13));
	}

	Board(double xStart, double yStart, double xFinish, double yFinish)
		: m_xStart{ xStart }, m_yStart{ yStart }, m_xFinish{ xFinish }, m_yFinish{ yFinish },
		ball{ m_xStart, m_yStart, 0.0, 0.0 }
	{

	}

	void Reset();
	void Reset(double xStart, double yStart);

	void Update(double theta_dot, double phi_dot);

	void Compute_Rates_Of_Change(double theta_dot, double phi_dot);

	void Apply_Euler_Integration(double dt, double theta_dot, double phi_dot);

	Terminal Check_Termination();

	double GetXp() { return ball.m_xp; }
	double GetYp() { return ball.m_yp; }
	double GetVxp() { return ball.m_vxp; }
	double GetVyp() { return ball.m_vyp; }

	void Print_Pos() { cout << "Ball is at (" << ball.m_xp << ", " << ball.m_yp << ")\n"; }
};
