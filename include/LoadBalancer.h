#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include "Packet.h"

class Server {
public:
    Server() : m_currentLoad(0) {}
    void addPacket(const Packet& packet);
    uint32_t getCurrentLoad() const { return m_currentLoad; }
    void resetLoad() { m_currentLoad = 0; }

private:
    uint32_t m_currentLoad;
};

class LoadBalancer {
public:
    LoadBalancer(int serverCount, double serverCapacity);
    void distributePacket(const Packet& packet);
    void monitorAndAdjust();
    size_t getServerCount() const { return m_servers.size(); }
    uint32_t getServerLoad(size_t index) const { return m_servers[index].getCurrentLoad(); }

private:
    std::vector<Server> m_servers;
    double m_serverCapacity;
};

#endif // LOAD_BALANCER_H

