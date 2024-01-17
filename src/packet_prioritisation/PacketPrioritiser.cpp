//This code simulates the prioritisation of different types of data packets.

#include "PacketPrioritiser.h"
#include <iostream>
#include <queue>
#include <vector>

// Function to simulate packet prioritisation
std::queue<Packet> prioritisePackets(const std::vector<Packet>& packets) {
    std::queue<Packet> prioritisedQueue;

    // Prioritize high priority packets first
    for (const auto& packet : packets) {
        if (packet.type == 1) {
            prioritisedQueue.push(packet);
        }
    }

    // Then add normal priority packets
    for (const auto& packet : packets) {
        if (packet.type == 0) {
            prioritisedQueue.push(packet);
        }
    }

    return prioritisedQueue;
}

int main() {
    std::vector<Packet> packets = {{1, 100}, {0, 200}, {1, 50}};
    std::queue<Packet> prioritisedPackets = prioritisePackets(packets);

    while (!prioritisedPackets.empty()) {
        Packet p = prioritisedPackets.front();
        std::cout << "Packet Type: " << p.type << ", Size: " << p.size << "\n";
        prioritisedPackets.pop();
    }
    return 0;
}
