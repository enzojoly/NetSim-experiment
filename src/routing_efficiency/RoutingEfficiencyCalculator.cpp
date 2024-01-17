//Calculating the efficiency of different routing paths in a network.

#include "RoutingEfficiencyCalculator.h"
#include <vector>

// Function to calculate routing path efficiency
double calculatePathEfficiency(const std::vector<int>& path, int maxHops) {
    return static_cast<double>(path.size()) / maxHops;
}
