//Randomly simulating network failures in a distributed system.

#include "NetworkFailureSimulator.h"
#include <random>

// Function to simulate network failures
bool simulateNetworkFailure(double failureProbability) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution d(failureProbability);

    return d(gen);
}
