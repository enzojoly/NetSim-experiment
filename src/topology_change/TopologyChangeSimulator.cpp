//Simulating the impact of changes in network topology on data flow.

#include "TopologyChangeSimulator.h"

// Function to simulate the impact of topology change
int simulateTopologyChangeImpact(int nodes) {
    // Assuming each node adds a fixed delay
    const int delayPerNode = 5; // milliseconds
    return nodes * delayPerNode;
}
