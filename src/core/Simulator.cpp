#include "Simulator.h"
#include <fstream>
#include <iostream>
#include <sstream>

Simulator::Simulator(int initialNodeCount, double simulationDuration, double snapshotInterval)
    : m_simulationDuration(simulationDuration),
      m_snapshotInterval(snapshotInterval),
      m_lastSnapshotTime(0.0),
      m_clock(SimulationClock::getInstance()) {
    initializeComponents(initialNodeCount);
}

void Simulator::run() {
    m_clock.start();
    while (m_clock.getCurrentTime() < m_simulationDuration) {
        simulateNetworkDynamics();
        updateComponentStates();

        auto packets = m_packetTransmission->simulateTransmission(1.0);  // Generate packets for 1 second
        processPackets(packets);

        if (m_clock.getCurrentTime() - m_lastSnapshotTime >= m_snapshotInterval) {
            takeSnapshot();
            m_lastSnapshotTime = m_clock.getCurrentTime();
        }

        m_clock.advanceTime(1.0);  // Advance simulation by 1 second
    }
    m_clock.stop();
    logSimulationResults();
}

void Simulator::takeSnapshot() {
    std::string snapshot = generateSnapshot();
    std::cout << "Snapshot at time " << m_clock.getCurrentTime() << ":\n" << snapshot << std::endl;

    std::ofstream logFile("simulation_snapshots.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Snapshot at time " << m_clock.getCurrentTime() << ":\n" << snapshot << "\n-------------------------------------------\n";
        logFile.close();
    } else {
        std::cerr << "Unable to open log file for writing snapshots." << std::endl;
    }
}

std::string Simulator::generateSnapshot() const {
    std::ostringstream ss;
    ss << "Network Congestion Level: " << m_networkCongestion->getCurrentCongestionLevel() << "\n";
    ss << "Current Bandwidth Utilisation: " << m_bandwidthUtilization->getCurrentUtilization() << " Mbps\n";
    ss << "Network Error Rate: " << m_errorRateModel->getCurrentErrorRate() << "\n";
    ss << "Load Balancing Simulation:\n";
    for (size_t i = 0; i < m_loadBalancer->getServerCount(); ++i) {
        ss << "Path " << i << ": " << m_loadBalancer->getServerLoad(i) << " units of load\n";
    }
    for (int i = 0; i < 10; ++i) {  // 10 sample delays
        ss << "Network Delay: " << m_networkDelay->simulateDelays({Packet(0, Packet::Priority::MEDIUM, 1000, 0)})[0] << " seconds\n";
    }
    ss << "Network Failure: " << (m_topologyManager->hasAnyFailure() ? "Yes" : "No") << "\n";
    ss << "Routing Path Efficiency: " << m_routingEfficiency->calculateEfficiency() << "\n";
    return ss.str();
}

void Simulator::initializeComponents(int initialNodeCount) {
    m_packetTransmission = std::make_unique<PacketTransmission>(1000.0);  // 1000 packets per second on average
    m_bandwidthUtilization = std::make_unique<BandwidthUtilization>(1000.0);  // 1 Gbps max bandwidth
    m_errorRateModel = std::make_unique<ErrorRateModel>(0.0001);  // 0.01% base error rate
    m_loadBalancer = std::make_unique<LoadBalancer>(5, 200.0);  // 5 servers, 200 Mbps capacity each
    m_networkCongestion = std::make_unique<NetworkCongestion>(1000.0);  // 1 Gbps link capacity
    m_networkDelay = std::make_unique<NetworkDelay>(0.01, 0.001);  // 10ms base delay, 1ms jitter
    m_topologyManager = std::make_shared<TopologyManager>(initialNodeCount);
    m_routingEfficiency = std::make_unique<RoutingEfficiency>(m_topologyManager);
    m_packetPrioritizer = std::make_unique<PacketPrioritizer>();

    m_topologyManager->generateInitialTopology();
}

void Simulator::simulateNetworkDynamics() {
    m_topologyManager->simulateTopologyChanges(1.0);  // Simulate changes for 1 second
    m_routingEfficiency->recalculateRoutes();
}

void Simulator::updateComponentStates() {
    double congestionLevel = m_networkCongestion->getCurrentCongestionLevel();
    double errorRate = m_errorRateModel->getCurrentErrorRate();
    double bandwidth = m_bandwidthUtilization->getCurrentUtilization();

    m_networkDelay->updateDelayParameters(congestionLevel);
    m_errorRateModel->updateEnvironmentalFactors(30.0 - congestionLevel * 10, congestionLevel * 0.1, 100.0);
    m_packetPrioritizer->updatePrioritizationParameters(congestionLevel, errorRate);
    m_loadBalancer->monitorAndAdjust();

    // Use bandwidth variable to avoid unused variable warning
    m_bandwidthUtilization->updateUtilization({Packet(0, Packet::Priority::MEDIUM, static_cast<uint32_t>(bandwidth), 0)});
}

void Simulator::processPackets(const std::vector<Packet>& packets) {
    auto prioritizedPackets = m_packetPrioritizer->prioritizePackets(packets);
    auto errors = m_errorRateModel->simulateErrors(prioritizedPackets);
    auto correctedPackets = m_errorRateModel->applyErrorCorrectionAndRetransmission(prioritizedPackets, errors);

    m_bandwidthUtilization->updateUtilization(correctedPackets);
    m_networkCongestion->updateCongestion(correctedPackets);

    for (const auto& packet : correctedPackets) {
        m_loadBalancer->distributePacket(packet);
    }

    auto delays = m_networkDelay->simulateDelays(correctedPackets);

    // Here you might want to log or analyze the processed packets and their delays
}

void Simulator::logSimulationResults() {
    std::ofstream logFile("simulation_results.log", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Simulation completed. Duration: " << m_simulationDuration << " seconds\n";
        logFile << "Final bandwidth utilization: " << m_bandwidthUtilization->getCurrentUtilization() << "%\n";
        logFile << "Final congestion level: " << m_networkCongestion->getCurrentCongestionLevel() << "\n";
        logFile << "Final error rate: " << m_errorRateModel->getCurrentErrorRate() << "\n";
        logFile << "Final routing efficiency: " << m_routingEfficiency->calculateEfficiency() << "\n";
        logFile << "-------------------------------------------\n";
        logFile.close();
    } else {
        std::cerr << "Unable to open log file for writing results." << std::endl;
    }
}
