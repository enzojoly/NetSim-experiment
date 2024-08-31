#include "LoadBalancer.h"
#include <algorithm>

LoadBalancer::LoadBalancer(int serverCount, double serverCapacity)
    : m_serverCapacity(serverCapacity) {
    m_servers.resize(serverCount);
}

void Server::addPacket(const Packet& packet) {
    m_currentLoad += packet.getSize();
    // Additional logic for adding packets might go here
}

void LoadBalancer::distributePacket(const Packet& packet) {
    // Simple round-robin distribution
    static size_t currentServer = 0;
    m_servers[currentServer].addPacket(packet);
    currentServer = (currentServer + 1) % m_servers.size();
}

void LoadBalancer::monitorAndAdjust() {
    // Implement monitoring and load adjustment logic here
    // Example:
    for (auto& server : m_servers) {
        if (server.getCurrentLoad() > m_serverCapacity) {
            // Redistribute load or alert
            // For now, we'll just reset the load
            server.resetLoad();
        }
    }
}
