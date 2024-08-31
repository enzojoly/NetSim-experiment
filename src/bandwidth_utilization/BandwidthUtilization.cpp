#include "BandwidthUtilization.h"
#include <numeric>
#include <algorithm>

BandwidthUtilization::BandwidthUtilization(double maxBandwidth)
    : m_maxBandwidth(maxBandwidth), m_currentUtilization(0.0) {}

double BandwidthUtilization::simulateUtilisation(const std::vector<Packet>& packets, double duration) {
    double totalDataTransferred = std::accumulate(packets.begin(), packets.end(), 0.0,
        [](double sum, const Packet& p) { return sum + p.getSize(); });

    // Calculate utilization as a percentage of max bandwidth
    double utilizationPercentage = (totalDataTransferred * 8) / (m_maxBandwidth * duration) * 100;

    // Ensure utilization doesn't exceed 100%
    m_currentUtilization = std::min(100.0, utilizationPercentage);

    return m_currentUtilization;
}

void BandwidthUtilization::updateUtilization(const std::vector<Packet>& packets) {
    // This method can be used for real-time updates during simulation
    // For now, it's a simplified version of simulateUtilisation
    double totalData = std::accumulate(packets.begin(), packets.end(), 0.0,
        [](double sum, const Packet& p) { return sum + p.getSize(); });

    // Assume a 1-second interval for this update
    double utilizationPercentage = (totalData * 8) / m_maxBandwidth * 100;
    m_currentUtilization = std::min(100.0, utilizationPercentage);
}

double BandwidthUtilization::getCurrentUtilization() const {
    return m_currentUtilization;
}
