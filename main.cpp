#include <iostream>
//#include "src/common/Packet.h"
//#include "src/common/Utils.h"
//#include "src/packet_prioritisation/PacketPrioritiser.h"
#include "src/network_congestion/NetworkCongestionSimulator.h"
#include "src/bandwidth_utilisation/BandwidthUtilisationSimulator.h"
#include "src/error_rate/ErrorRateSimulator.h"
#include "src/load_balancing/LoadBalancerSimulator.h"
#include "src/network_delay/NetworkDelaySimulator.h"
#include "src/network_failures/NetworkFailureSimulator.h"
#include "src/packet_transmission/PacketTransmissionSimulator.h"
#include "src/routing_efficiency/RoutingEfficiencyCalculator.h"
#include "src/topology_change/TopologyChangeSimulator.h"

int main() {
    // Packet prioritisation
/*    std::vector<Packet> packets = {{1, 100}, {0, 200}, {1, 50}};
    std::vector<Packet> prioritisedPackets = prioritisePackets(packets);
    std::cout << "Prioritized Packets:\n";
    printPackets(prioritisedPackets);
*/


    // Network congestion
    double dataRate = 1000.0; // in Mbps
    double packetSize = 100.0; // in MB
    double congestionLevel = simulateNetworkCongestion(dataRate, packetSize);
    std::cout << "Network Congestion Level: " << congestionLevel << std::endl;


    // Bandwidth utilisation
    double maxBandwidth = 100.0;
    double currentUtilisation = simulateBandwidthUtilisation(maxBandwidth);
    std::cout << "Current Bandwidth Utilisation: " << currentUtilisation << " Mbps\n";


    // Network error rate
    double signalNoiseRatio = 30.0;
    double errorRate = simulateErrorRate(signalNoiseRatio);
    std::cout << "Network Error Rate: " << errorRate << "\n";


    // Load balancing
    int paths = 3;
    double totalLoad = 100.0;
    auto loads = simulateLoadBalancing(paths, totalLoad);

    std::cout << "Load Balancing Simulation:\n";
    for (int i = 0; i < loads.size(); ++i) {
        std::cout << "Path " << i << ": " << loads[i] << " units of load\n";
    }


    // Network delay
    double rate = 0.5;
    int duration = 10;
    auto delays = simulateNetworkDelay(rate, duration);
    for (auto delay : delays) {
        std::cout << "Network Delay: " << delay << " seconds\n";
    }


    // Network failures
    double failureProbability = 0.1;
    bool failureOccurred = simulateNetworkFailure(failureProbability);
    std::cout << "Network Failure: " << (failureOccurred ? "Yes" : "No") << "\n";


    // Packet transmission
    int lambda = 4;
    auto transmittedPackets = simulatePacketTransmission(lambda, duration);
    std::cout << "Packet Transmission Counts:\n";
    for (auto count : transmittedPackets) {
        std::cout << count << " ";
    }
    std::cout << "\n";


    // Routing efficiency
    std::vector<int> path = {1, 2, 3, 4};
    int maxHops = 10;
    double efficiency = calculatePathEfficiency(path, maxHops);
    std::cout << "Routing Path Efficiency: " << efficiency << "\n";


    // Topology change
    int nodes = 10;
    int impact = simulateTopologyChangeImpact(nodes);
    std::cout << "Impact on Data Flow: " << impact << " ms\n";


    return 0;
}
