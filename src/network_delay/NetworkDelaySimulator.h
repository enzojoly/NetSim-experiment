#ifndef NETWORK_DELAY_SIMULATOR_H
#define NETWORK_DELAY_SIMULATOR_H

#include <vector>

// Simulate network delay using exponential distribution
std::vector<double> simulateNetworkDelay(double rate, int duration);

#endif // NETWORK_DELAY_SIMULATOR_H

