#pragma once

#include <iostream>
#include <vector>

#include "../../model/environment/Wall.h"
#include "../../model/environment/Hole.h"

using namespace std;

enum class algo_type
{
	P_FIELD,
	MANUAL
};

class Gnc_Guid
{
private:

public:
	// Gains
	double k_attract{ 5.0 }; // Attractive constant for potential field
	double k_repulse{ 0.1 }; // Repulsive constant for potential field
	double k_damp{ 0.000 }; // Damping constant for potential field

	double max_vel_cmd{ 0.5 }; // Max commandable acceleration [m/sec]

	// Waypoints
	int wp_idx{ 0 }; // Index of current wp []
	double wp_to_x{ 0.1 }; // Current wp, x-coordinate [m]
	double wp_to_y{ 0.1 }; // Current wp, y-coordinate [m]
	double wp_radius{ 0.005 }; // Capture radius for wp [m]

	vector<double> wp_x_list; // List of all wp x-coordinates, in order [m]
	vector<double> wp_y_list; // List of all wp y-coordinates, in order [m]

	// Walls
	vector<Wall> walls;
	vector<Hole> holes;

	// Time
	double dt{ 0.01 }; // Time in between Update() [sec]

	// Output
	double vel_cmd_x{ 0.0 }; // Acceleration command x-component [m/sec] 
	double vel_cmd_y{ 0.0 }; // Acceleration command y-component [m/sec] 

	double vel_attract_x{ 0.0 }; // Attractive component of vel_cmd_x due to wp_to [m/sec]
	double vel_attract_y{ 0.0 }; // Attractive component of vel_cmd_y due to wp_to [m/sec]

	double vel_wall_x{ 0.0 }; // Repulsive component of vel_cmd_x due to walls [m/sec]
	double vel_wall_y{ 0.0 }; // Repulsive component of vel_cmd_y due to walls [m/sec]

	double vel_hole_x{ 0.0 }; // Repulsive component of vel_cmd_x due to holes [m/sec]
	double vel_hole_y{ 0.0 }; // Repulsive component of vel_cmd_y due to holes [m/sec]

	double vel_damp_x{ 0.0 }; // Damping component of vel_cmd_x due to vel_xp [m/sec]
	double vel_damp_y{ 0.0 }; // Damping component of vel_cmd_y due to vel_yp [m/sec]

	void Init(double T_update);
	void Restart();
	void Update();

	void Init_WP_List();
	void Init_Walls();
	void Init_Holes();

	void Calc_Vel_Cmd();
	bool Reached_WP_To();
	void Update_WP_To();


	// State variables
	double xp{ 0.0 };
	double yp{ 0.0 };
	double vxp{ 0.0 };
	double vyp{ 0.0 };
};
