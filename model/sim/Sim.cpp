// Sim.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Sim.h"
#include "Sim_Episode.h"
#include "../environment/Board.h"
#include "../environment/Wall.h"

#include "../../gnc/exec/GNC_Exec.h"

//*********************************** OBJECT DEFINITIONS ******************************

// Simulation

Sim_Episode episode;

//--------------- Environment Models ---------------

Board board;

//Wall wall;

//--------------- GNC ---------------

extern Gnc_Exec exec;



int main()
{
    std::cout << "Hello World!\n";
    // Initiailize objects
    
    // Set global sim parameters
    int num_runs{ 1 };
    int run_type{ 1 };
    double timeout{ 30.0 };
    double sim_f{ 100.0 };
    double dt{ 1./sim_f };
    bool logging{ false };

    board.Init();

    exec.Init();

    for (int run_count = 1; run_count < num_runs + 1; ++run_count)
    {
        std::cout << "\nBeginning Episode #" << run_count << '\n';
        episode.Setup_Episode(run_type, dt, timeout, logging);
        
        episode.Run_Episode();

        std::cout << "Completed Episode #" << run_count << '\n';
        episode.Finish_Episode();
    }
}