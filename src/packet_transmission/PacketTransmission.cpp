#include "PacketTransmission.h"
#include "Packet.h"
#include <array>
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>

PacketTransmission::PacketTransmission(double avgPacketRate)
    : m_avgPacketRate(avgPacketRate),
      m_generator(std::random_device{}()),
      m_distribution(0.0, 1.0) {}

std::vector<Packet> PacketTransmission::simulateTransmission(double duration) {
    std::vector<Packet> packets;
    double time = 0;
    while (time < duration) {
        double interArrivalTime = -std::log(1.0 - m_distribution(m_generator)) / m_avgPacketRate;
        time += interArrivalTime;
        if (time < duration) {
            packets.push_back(generatePacket(time));
        }
    }
    std::sort(packets.begin(), packets.end(),
        [](const Packet& a, const Packet& b) { return a.getTimestamp() < b.getTimestamp(); });
    return packets;
}

void PacketTransmission::logPacketGenerationTimes(const std::vector<Packet>& packets) {
    std::ofstream logFile("packet_generation_times.csv");
    if (logFile.is_open()) {
        for (const auto& packet : packets) {
            logFile << packet.getTimestamp() << "," << packet.getSize() << "\n";
        }
        logFile.close();
    } else {
        std::cerr << "Unable to open file for logging packet generation times." << std::endl;
    }
}

Packet PacketTransmission::generatePacket(double currentTime) {
    static std::array<std::uniform_int_distribution<>, 3> sizeRanges = {
        std::uniform_int_distribution<>(64, 64),   // Minimum Ethernet frame size
        std::uniform_int_distribution<>(65, 1230), // Medium packets
        std::uniform_int_distribution<>(1231, 1500) // Maximum Ethernet frame size without jumbo frames
    };
    int sizeCategory = (m_distribution(m_generator) < 0.8) ? 0 : ((m_distribution(m_generator) < 0.95) ? 1 : 2);
    uint32_t packetSize = sizeRanges[sizeCategory](m_generator);
    return Packet(currentTime, packetSize);
}
