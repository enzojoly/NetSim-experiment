#ifndef ROUTING_EFFICIENCY_H
#define ROUTING_EFFICIENCY_H

#include <vector>
#include <memory>
#include "TopologyManager.h"

class RoutingEfficiency {
public:
    RoutingEfficiency(std::shared_ptr<TopologyManager> topologyManager);
    double calculateEfficiency();
    void recalculateRoutes();
    const std::unordered_map<int, std::vector<int>>& getRoutingTable() const;

private:
    std::shared_ptr<TopologyManager> m_topologyManager;
    std::unordered_map<int, std::vector<int>> m_routingTable;

    std::vector<int> dijkstra(int source, int destination);
    double calculateRoutingOverhead();
    double calculateAveragePathLength();
};

#endif // ROUTING_EFFICIENCY_H

