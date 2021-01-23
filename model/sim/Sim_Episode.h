#pragma once

#include <iostream>
#include <vector>


enum class Run_Type {
	deterministic,
	random_draw
};

enum class Status {
	running,
	ended
};

class Sim_Episode {

public:

	void Setup_Episode(int type, double dt, double timeout, bool logging);
	void Run_Episode();
	void Finish_Episode();

	Status Get_Status() { return status; }

	Run_Type type{ Run_Type::deterministic };
	Status status{ Status::running };

private:

	double dt{ 0.01 }; // Timestep per loop [sec]
	double time{ 0.0 }; // Global episode timer [sec]
	double timeout{ 30.0 }; // Max time of episode [sec]
	bool logging{ false }; // Are we logging episode data?


};
