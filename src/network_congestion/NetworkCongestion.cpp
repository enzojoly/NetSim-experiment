#include "NetworkCongestion.h"
#include "SimulationClock.h"
#include <numeric>
#include <algorithm>
#include <cmath>

NetworkCongestion::NetworkCongestion(double linkCapacity)
    : m_linkCapacity(linkCapacity), m_currentCongestionLevel(0.0) {}

double NetworkCongestion::calculateCongestion(const std::vector<Packet>& packets, double duration) {
    double networkLoad = calculateNetworkLoad(packets, duration);

    // Calculate congestion level as a ratio of network load to link capacity
    m_currentCongestionLevel = networkLoad / m_linkCapacity;

    // Apply a non-linear scaling to emphasize high congestion levels
    m_currentCongestionLevel = std::min(1.0, std::pow(m_currentCongestionLevel, 1.5));

    return m_currentCongestionLevel;
}

void NetworkCongestion::simulateCongestionControl() {
    // Implement a simple TCP-like congestion control mechanism
    static double congestionWindow = 1.0;
    static int consecutiveAcks = 0;

    if (m_currentCongestionLevel < 0.5) {
        // Network is not congested, increase window size
        consecutiveAcks++;
        if (consecutiveAcks >= 3) {
            congestionWindow += 1.0;
            consecutiveAcks = 0;
        }
    } else {
        // Network is congested, reduce window size
        congestionWindow *= 0.5;
        consecutiveAcks = 0;
    }

    // Adjust link capacity based on congestion window
    m_linkCapacity = std::max(m_linkCapacity * (congestionWindow / 10.0), m_linkCapacity * 0.1);
}

double NetworkCongestion::getCurrentCongestionLevel() const {
    return m_currentCongestionLevel;
}

double NetworkCongestion::calculateNetworkLoad(const std::vector<Packet>& packets, double duration) {
    double totalDataTransferred = std::accumulate(packets.begin(), packets.end(), 0.0,
        [](double sum, const Packet& p) { return sum + p.getSize(); });

    // Convert bytes to bits and calculate data rate in bps
    double dataRate = (totalDataTransferred * 8) / duration;

    return dataRate;
}

void NetworkCongestion::updateCongestion(const std::vector<Packet>& packets) {
    // This method can be used for real-time updates during simulation
    // For now, it's a simplified version of calculateCongestion
    double duration = 1.0; // Assume 1 second for simplicity
    calculateCongestion(packets, duration);
}
