// GNC_Guid.cpp
// High-level path-planner
// Outputs acceleration command for the low-level controller

#include<iostream>
#include<vector>

#include "GNC_Guid.h"
#include "GNC_Nav.h"

// Utils
#include "../util/GNC_Inline.h"

//*************** OBJECT COLLABORATION ***************

extern Gnc_Nav nav;

//*************** OBJECT DEFINITION ***************

Gnc_Guid guid;

void Gnc_Guid::Init(double T_update)
{
	dt = T_update;

	Init_WP_List();
	Init_Walls();
	Init_Holes();
}

void Gnc_Guid::Init_WP_List()
{
	// WP 1
	wp_x_list.push_back(0.05);
	wp_y_list.push_back(0.05);

	// WP 2
	wp_x_list.push_back(-0.05);
	wp_y_list.push_back( 0.05);

	// WP 3
	wp_x_list.push_back(-0.05);
	wp_y_list.push_back(-0.05);

	// WP G
	wp_x_list.push_back( 0.05);
	wp_y_list.push_back(-0.05);
}

void Gnc_Guid::Init_Walls()
{

}

void Gnc_Guid::Init_Holes()
{

}

void Gnc_Guid::Restart()
{

	// Output
	vel_cmd_x = 0.0;
	vel_cmd_y = 0.0;

	vel_attract_x = 0.0;
	vel_attract_y = 0.0;

	vel_wall_x = 0.0;
	vel_wall_y = 0.0;

	vel_hole_x = 0.0;
	vel_hole_y = 0.0;

	vel_damp_x = 0.0;
	vel_damp_y = 0.0;

	// Waypoint
	wp_idx = 0;
	wp_to_x = wp_x_list[wp_idx];
	wp_to_y = wp_y_list[wp_idx];

	// State variable
	xp = 0.0;
	yp = 0.0;
	vxp = 0.0;
	vyp = 0.0;
}

void Gnc_Guid::Update()
{
	// Update state from GNC_Nav
	xp = nav.xp;
	yp = nav.yp;
	vxp = nav.vxp;
	vyp = nav.vyp;

	// Update Waypoint
	Update_WP_To();

	Calc_Vel_Cmd();
}

void Gnc_Guid::Update_WP_To()
{
	if (wp_idx + 1 == static_cast<int>(wp_x_list.size()))
	{
		return; // Don't change wp if it's the final one
	}
	else if (Reached_WP_To())
	{
		++wp_idx;
		wp_to_x = wp_x_list[wp_idx];
		wp_to_y = wp_y_list[wp_idx];
	}
}

bool Gnc_Guid::Reached_WP_To()
{
	if (DIST(xp, yp, wp_to_x, wp_to_y) < wp_radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Gnc_Guid::Calc_Vel_Cmd()
{
	// Artificial Potential Field
	vel_attract_x = k_attract * (wp_to_x - xp);
	vel_attract_y = k_attract * (wp_to_y - yp);

	vel_wall_x = 0.0;
	vel_wall_y = 0.0;
	for (int wall_count = 1; wall_count < walls.size(); ++wall_count)
	{

	}

	vel_hole_x = 0.0;
	vel_hole_y = 0.0;
	for (int hole_count = 1; hole_count < holes.size(); ++hole_count)
	{

	}

	vel_damp_x = -k_damp * vxp;
	vel_damp_y = -k_damp * vyp;

	// Total acceleration command
	vel_cmd_x = vel_attract_x + vel_wall_x + vel_hole_x + vel_damp_x;
	vel_cmd_y = vel_attract_y + vel_wall_y + vel_hole_y + vel_damp_y;

	vel_cmd_x = LIMIT(-max_vel_cmd, vel_cmd_x, max_vel_cmd);
	vel_cmd_y = LIMIT(-max_vel_cmd, vel_cmd_y, max_vel_cmd);
}
