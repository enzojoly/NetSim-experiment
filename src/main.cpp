#include "Simulator.h"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        // Default parameters
        int initialNodeCount = 10;
        double simulationDuration = 3600.0;  // 1 hour simulation
        double snapshotInterval = 300.0;  // 5 minutes

        // Parse command line arguments if provided
        if (argc > 1) initialNodeCount = std::stoi(argv[1]);
        if (argc > 2) simulationDuration = std::stod(argv[2]);
        if (argc > 3) snapshotInterval = std::stod(argv[3]);

        std::cout << "Starting NetSim simulation..." << std::endl;
        std::cout << "Initial node count: " << initialNodeCount << std::endl;
        std::cout << "Simulation duration: " << simulationDuration << " seconds" << std::endl;
        std::cout << "Snapshot interval: " << snapshotInterval << " seconds" << std::endl;

        // Create and run the simulator
        Simulator simulator(initialNodeCount, simulationDuration, snapshotInterval);
        simulator.run();

        std::cout << "Simulation completed. Check simulation_results.log and simulation_snapshots.log for details." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
