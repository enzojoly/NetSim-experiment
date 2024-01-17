//This code simulates the utilisation of bandwidth over time in a network.

#include "BandwidthUtilisationSimulator.h"
#include <iostream>
#include <random>

// Function to simulate bandwidth utilisation
double simulateBandwidthUtilisation(double maxBandwidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, maxBandwidth);

    return dis(gen);

    maxBandwidth = 100.0; // Maximum bandwidth in Mbps
    double currentUtilisation = simulateBandwidthUtilisation(maxBandwidth);
    std::cout << "Current Bandwidth Utilisation: " << currentUtilisation << " Mbps\n";
    return 0;
}
