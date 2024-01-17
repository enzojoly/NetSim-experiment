#ifndef PACKET_TRANSMISSION_SIMULATOR_H
#define PACKET_TRANSMISSION_SIMULATOR_H

#include <vector>

// Simulate packet transmission using a Poisson process
std::vector<int> simulatePacketTransmission(int lambda, int duration);

#endif // PACKET_TRANSMISSION_SIMULATOR_H

