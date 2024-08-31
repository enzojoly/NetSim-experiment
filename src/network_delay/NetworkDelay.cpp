#include "NetworkDelay.h"
#include "SimulationClock.h"
#include <algorithm>
#include <cmath>

NetworkDelay::NetworkDelay(double baseDelay, double jitterFactor)
    : m_baseDelay(baseDelay), m_jitterFactor(jitterFactor),
      m_generator(std::random_device{}()),
      m_delayDist(1.0 / baseDelay),
      m_jitterDist(0.0, jitterFactor * baseDelay) {}

std::vector<double> NetworkDelay::simulateDelays(const std::vector<Packet>& packets) {
    std::vector<double> delays;
    delays.reserve(packets.size());

    for (const auto& packet : packets) {
        double delay = calculatePacketDelay(packet);
        delays.push_back(delay);
    }

    return delays;
}

void NetworkDelay::updateDelayParameters(double networkLoad) {
    // Adjust base delay based on network load
    double loadFactor = 1.0 + std::pow(networkLoad, 2);  // Non-linear increase with load
    double newBaseDelay = m_baseDelay * loadFactor;

    // Update exponential distribution with new rate parameter
    m_delayDist = std::exponential_distribution<>(1.0 / newBaseDelay);

    // Adjust jitter based on network load
    double newJitterFactor = m_jitterFactor * (1.0 + networkLoad);
    m_jitterDist = std::normal_distribution<>(0.0, newJitterFactor * newBaseDelay);
}

double NetworkDelay::calculatePacketDelay(const Packet& packet) {
    // Base delay from exponential distribution
    double baseDelay = m_delayDist(m_generator);

    // Add size-dependent delay component
    double sizeFactor = std::log2(packet.getSize() / 64.0);  // Logarithmic scaling
    double sizeDelay = m_baseDelay * sizeFactor * 0.1;  // 10% of base delay per doubling of size

    // Apply jitter
    double totalDelay = baseDelay + sizeDelay;
    return applyJitter(totalDelay);
}

double NetworkDelay::applyJitter(double delay) {
    double jitter = m_jitterDist(m_generator);
    return std::max(0.0, delay + jitter);  // Ensure non-negative delay
}
