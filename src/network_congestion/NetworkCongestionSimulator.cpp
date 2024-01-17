//This code simulates network congestion based on varying data rates and packet sizes.

#include "NetworkCongestionSimulator.h"
#include <iostream>

// Function to simulate network congestion
double simulateNetworkCongestion(double dataRate, double packetSize) {
    return dataRate / packetSize;

    dataRate = 1000.0; // Data rate in Mbps
    packetSize = 100.0; // Packet size in MB
    double congestionLevel = simulateNetworkCongestion(dataRate, packetSize);

    std::cout << "Network Congestion Level: " << congestionLevel << "\n";
    return 0;
}
