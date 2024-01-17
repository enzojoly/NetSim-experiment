//Exponential distribution is useful for modeling the time between events in a process that occurs continuously and independently at a constant average rate.

#include "NetworkDelaySimulator.h"
#include <random>
#include <vector>

// Simulate network delay using exponential distribution
std::vector<double> simulateNetworkDelay(double rate, int duration) {
    std::vector<double> delays;
    std::default_random_engine generator;
    std::exponential_distribution<double> distribution(rate);

    for(int t = 0; t < duration; ++t) {
        delays.push_back(distribution(generator));
    }
    return delays;
}
