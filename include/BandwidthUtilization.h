#ifndef BANDWIDTH_UTILIZATION_H
#define BANDWIDTH_UTILIZATION_H

#include <vector>
#include "Packet.h"

class BandwidthUtilization {
public:
    BandwidthUtilization(double maxBandwidth);
    double simulateUtilisation(const std::vector<Packet>& packets, double duration);
    void updateUtilization(const std::vector<Packet>& packets);
    double getCurrentUtilization() const;

private:
    double m_maxBandwidth;
    double m_currentUtilization;
};

#endif // BANDWIDTH_UTILIZATION_H

