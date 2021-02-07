#pragma once


enum class Gnc_Mode
{
	STANDBY,
	MANUAL,
	NAVIGATE
};

class Gnc_Exec
{
private:

public:
	// Update rates
	int exec_f{ 100 }; // GNC Executive update rate [Hz]
	int nav_f{ 100 }; // GNC Navigation update rate [Hz]
	int guid_f{ 100 }; // GNC Guidance udpate rate [Hz]
	int control_f{ 100 }; // GNC Control update rate [Hz]

	double exec_T{ 1. / exec_f }; // GNC Executive period [sec]
	double nav_T{ 1. / nav_f }; // GNC Navigation period [sec]
	double guid_T{ 1. / guid_f }; // GNC Guidance period [sec]
	double control_T{ 1. / control_f }; // GNC Control period [sec]

	int nav_n_cycles{ exec_f / nav_f }; // Number of exec updates per nav update []
	int guid_n_cycles{ exec_f / guid_f }; // Number of exec updates per guid update []
	int control_n_cycles{ exec_f / control_f }; // Number of exec updates per control update []

	double timer{ 0.0 }; // Global timer for GNC [sec]
	int cycle_counter{ 1 }; // Counts the number of cycles []

	bool logging{ false };

	void Init();
	void Restart();
	void Update();

	Gnc_Mode exec_mode{ Gnc_Mode::STANDBY };

};
