// Sim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Sim.h"
#include "Sim_Episode.h"
#include "../environment/Board.h"
#include "../environment/Wall.h"

//*********************************** OBJECT DEFINITIONS ******************************

// Simulation

Sim_Episode episode;

//--------------- Environment Models ---------------

Board board;

//Wall wall;



int main()
{
    std::cout << "Hello World!\n";
    // Initiailize objects
    
    // Set global sim parameters
    int num_runs{ 3 };
    int run_type{ 1 };
    double timeout{ 30.0 };
    double dt{ 0.01 };
    bool logging{ false };

    for (int run_count = 1; run_count < num_runs + 1; ++run_count)
    {
        std::cout << "\nBeginning Episode #" << run_count << '\n';
        episode.Setup_Episode(run_type, dt, timeout, logging);
        
        episode.Run_Episode();

        std::cout << "Completed Episode #" << run_count << '\n';
        episode.Finish_Episode();
    }
}