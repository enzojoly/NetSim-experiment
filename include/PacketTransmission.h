#ifndef PACKET_TRANSMISSION_H
#define PACKET_TRANSMISSION_H

#include <random>
#include <vector>
#include "Packet.h"

class PacketTransmission {
public:
    PacketTransmission(double avgPacketRate);
    std::vector<Packet> simulateTransmission(double duration);
    void logPacketGenerationTimes(const std::vector<Packet>& packets);
    Packet generatePacket(double currentTime);

private:
    double m_avgPacketRate;
    std::mt19937 m_generator;
    std::uniform_real_distribution<> m_distribution;
};

#endif // PACKET_TRANSMISSION_H

