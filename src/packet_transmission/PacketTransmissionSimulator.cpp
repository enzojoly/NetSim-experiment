//The Poisson process is a statistical model often used in network theory to represent events (like packet transmissions) that occur independently at a constant average rate.

#include "PacketTransmissionSimulator.h"
#include <random>
#include <vector>

// Simulate packet transmission using a Poisson process
std::vector<int> simulatePacketTransmission(int lambda, int duration) {
    std::vector<int> packets;
    std::default_random_engine generator;
    std::poisson_distribution<int> distribution(lambda);

    // Each iteration represents a time unit, generating the number of packets sent
    for(int t = 0; t < duration; ++t) {
        packets.push_back(distribution(generator));
    }
    return packets;
}
