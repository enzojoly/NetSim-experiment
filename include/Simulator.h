#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <memory>
#include <vector>
#include <string>
#include "SimulationClock.h"
#include "PacketTransmission.h"
#include "BandwidthUtilization.h"
#include "ErrorRateModel.h"
#include "LoadBalancer.h"
#include "NetworkCongestion.h"
#include "NetworkDelay.h"
#include "TopologyManager.h"
#include "RoutingEfficiency.h"
#include "PacketPrioritizer.h"
#include "Packet.h"

class Simulator {
public:
    Simulator(int initialNodeCount, double simulationDuration, double snapshotInterval = 300.0);
    void run();

private:
    void initializeComponents(int initialNodeCount);
    void simulateNetworkDynamics();
    void updateComponentStates();
    void processPackets(const std::vector<Packet>& packets);
    void logSimulationResults();
    void takeSnapshot();
    std::string generateSnapshot() const;

    double m_simulationDuration;
    double m_snapshotInterval;
    double m_lastSnapshotTime;
    SimulationClock& m_clock;
    std::unique_ptr<PacketTransmission> m_packetTransmission;
    std::unique_ptr<BandwidthUtilization> m_bandwidthUtilization;
    std::unique_ptr<ErrorRateModel> m_errorRateModel;
    std::unique_ptr<LoadBalancer> m_loadBalancer;
    std::unique_ptr<NetworkCongestion> m_networkCongestion;
    std::unique_ptr<NetworkDelay> m_networkDelay;
    std::shared_ptr<TopologyManager> m_topologyManager;
    std::unique_ptr<RoutingEfficiency> m_routingEfficiency;
    std::unique_ptr<PacketPrioritizer> m_packetPrioritizer;
};

#endif // SIMULATOR_H

