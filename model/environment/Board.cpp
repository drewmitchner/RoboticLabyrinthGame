#include <iostream>
#include <vector>

#include "Board.h"

extern Board board;

void Board::Reset()
{
	board.Reset(0.0, 0.0);
}

void Board::Reset(double xStart, double yStart)
{
	board.ball.m_xp			= xStart;
	board.ball.m_yp			= yStart;
	board.ball.m_vxp		= 0.0;
	board.ball.m_vyp		= 0.0;
	board.ball.m_vxp_dot	= 0.0;
	board.ball.m_vyp_dot	= 0.0;

	board.m_theta			= 0.0;
	board.m_phi				= 0.0;
}

void Board::Update(double theta_dot, double phi_dot)
{
	Compute_Rates_Of_Change(theta_dot, phi_dot);

	Apply_Euler_Integration(0.01, theta_dot, phi_dot);
}

void Board::Compute_Rates_Of_Change(double theta_dot, double phi_dot)
{
	// Decoupled accels (simplification, innacurate but maybe good enough?)
	//m_ball.m_vxp_dot = (5.0 / 7.0) * ( G0 * sin(board.m_theta) + ball.m_xp * pow(theta_dot,2));
	//m_ball.m_vyp_dot = (5.0 / 7.0) * (-G0 * sin(board.m_phi) + ball.m_yp * pow(phi_dot, 2));

	ball.m_vxp_dot = (5.0 / 7.0) * (G0 * sin(board.m_theta) +
		//cos(board.m_phi) * theta_dot * phi_dot * ball.m_yp +
		ball.m_xp * pow(theta_dot, 2) -
		ball.m_yp * theta_dot * phi_dot +
		sin(board.m_phi) * theta_dot * phi_dot * ball.m_vyp -
		sin(board.m_phi) * ball.m_vyp * theta_dot);

	ball.m_vyp_dot = (5.0 / 7.0) * (-G0 * cos(board.m_theta) * sin(board.m_phi) +
		ball.m_yp * pow(phi_dot, 2) +
		ball.m_xp * theta_dot * phi_dot);
}

void Board::Apply_Euler_Integration(double dt, double theta_dot, double phi_dot)
{
	// Integrate Ball state first
	ball.m_xp += dt * ball.m_vxp;
	ball.m_yp += dt * ball.m_vyp;

	ball.m_vxp += dt * ball.m_vxp_dot;
	ball.m_vyp += dt * ball.m_vyp_dot;

	// Integrate Board state
	board.m_theta += dt * theta_dot;
	board.m_phi += dt * phi_dot;
}

Terminal Board::Check_Termination()
{
	for (int wall_count = 0; wall_count < walls.size(); ++wall_count)
	{
		if (walls[wall_count].Get_Distance(ball.m_xp, ball.m_yp) < ball.m_radius + walls[wall_count].Get_Width())
		{
			return Terminal::wall_collision;
		}
	}

	return Terminal::continue_run;
}
