#ifndef NETWORK_DELAY_H
#define NETWORK_DELAY_H

#include <vector>
#include <random>
#include "Packet.h"

class NetworkDelay {
public:
    NetworkDelay(double baseDelay, double jitterFactor);

    // Simulate delays for a batch of packets
    std::vector<double> simulateDelays(const std::vector<Packet>& packets);

    // Update delay parameters based on network load
    void updateDelayParameters(double networkLoad);

private:
    double m_baseDelay;
    double m_jitterFactor;
    std::mt19937 m_generator;
    std::exponential_distribution<> m_delayDist;
    std::normal_distribution<> m_jitterDist;

    // Calculate delay for a single packet
    double calculatePacketDelay(const Packet& packet);

    // Apply jitter to a delay value
    double applyJitter(double delay);
};

#endif // NETWORK_DELAY_H

