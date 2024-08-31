#include "PacketPrioritizer.h"
#include <algorithm>

PacketPrioritizer::PacketPrioritizer()
    : m_congestionFactor(1.0), m_errorRateFactor(1.0) {}

std::vector<Packet> PacketPrioritizer::prioritizePackets(const std::vector<Packet>& packets) {
    // Clear the priority queue
    while (!m_priorityQueue.empty()) {
        m_priorityQueue.pop();
    }

    // Add packets to the priority queue with dynamic priority
    for (const auto& packet : packets) {
        Packet prioritizedPacket = packet;
        double dynamicPriority = calculateDynamicPriority(packet);
        Packet::Priority newPriority;
        if (dynamicPriority < 1.0) newPriority = Packet::Priority::LOW;
        else if (dynamicPriority < 2.0) newPriority = Packet::Priority::MEDIUM;
        else newPriority = Packet::Priority::HIGH;
        prioritizedPacket.setPriority(newPriority);
        m_priorityQueue.push(prioritizedPacket);
    }

    // Extract packets from the priority queue
    std::vector<Packet> prioritizedPackets;
    prioritizedPackets.reserve(packets.size());

    while (!m_priorityQueue.empty()) {
        prioritizedPackets.push_back(m_priorityQueue.top());
        m_priorityQueue.pop();
    }

    // Reverse the vector to have highest priority first
    std::reverse(prioritizedPackets.begin(), prioritizedPackets.end());

    return prioritizedPackets;
}

void PacketPrioritizer::updatePrioritizationParameters(double congestionLevel, double errorRate) {
    m_congestionFactor = 1.0 + congestionLevel;  // Increase priority with congestion
    m_errorRateFactor = 1.0 / (1.0 + errorRate);  // Decrease priority with high error rates
}

double PacketPrioritizer::calculateDynamicPriority(const Packet& packet) const {
    double basePriority = static_cast<double>(packet.getPriority());

    // Apply congestion and error rate factors
    double dynamicPriority = basePriority * m_congestionFactor * m_errorRateFactor;

    // Consider packet age (older packets get higher priority)
    double ageBoost = (SimulationClock::getInstance().getCurrentTime() - packet.getTimestamp()) / 1000.0;
    dynamicPriority += ageBoost;

    // Consider packet size (smaller packets get slightly higher priority)
    double sizeBoost = 1.0 - (static_cast<double>(packet.getSize()) / 1518.0);  // 1518 is max Ethernet frame size
    dynamicPriority += sizeBoost;

    return dynamicPriority;
}
