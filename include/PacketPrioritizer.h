#ifndef PACKET_PRIORITIZER_H
#define PACKET_PRIORITIZER_H

#include <vector>
#include <queue>
#include "Packet.h"
#include "SimulationClock.h"

class PacketPrioritizer {
public:
    PacketPrioritizer();
    std::vector<Packet> prioritizePackets(const std::vector<Packet>& packets);
    void updatePrioritizationParameters(double congestionLevel, double errorRate);

private:
    struct PacketComparator {
        bool operator()(const Packet& p1, const Packet& p2) const {
            return static_cast<int>(p1.getPriority()) < static_cast<int>(p2.getPriority());
        }
    };

    std::priority_queue<Packet, std::vector<Packet>, PacketComparator> m_priorityQueue;
    double m_congestionFactor;
    double m_errorRateFactor;

    double calculateDynamicPriority(const Packet& packet) const;
};

#endif // PACKET_PRIORITIZER_H

