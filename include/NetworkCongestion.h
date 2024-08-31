#ifndef NETWORK_CONGESTION_H
#define NETWORK_CONGESTION_H

#include <vector>
#include "Packet.h"

class NetworkCongestion {
public:
    NetworkCongestion(double linkCapacity);
    double calculateCongestion(const std::vector<Packet>& packets, double duration);
    void simulateCongestionControl();
    double getCurrentCongestionLevel() const;
    void updateCongestion(const std::vector<Packet>& packets);

private:
    double m_linkCapacity;
    double m_currentCongestionLevel;
    double calculateNetworkLoad(const std::vector<Packet>& packets, double duration);
};

#endif // NETWORK_CONGESTION_H

