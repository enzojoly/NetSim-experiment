#include "RoutingEfficiency.h"
#include <queue>
#include <limits>
#include <algorithm>

RoutingEfficiency::RoutingEfficiency(std::shared_ptr<TopologyManager> topologyManager)
    : m_topologyManager(topologyManager) {
    recalculateRoutes();
}

double RoutingEfficiency::calculateEfficiency() {
    double averagePathLength = calculateAveragePathLength();
    double routingOverhead = calculateRoutingOverhead();

    // Efficiency is inversely proportional to path length and overhead
    return 1.0 / (averagePathLength * (1.0 + routingOverhead));
}

void RoutingEfficiency::recalculateRoutes() {
    m_routingTable.clear();
    const auto& nodes = m_topologyManager->getNodes();

    for (const auto& source : nodes) {
        for (const auto& destination : nodes) {
            if (source != destination) {
                m_routingTable[source->getId()] = dijkstra(source->getId(), destination->getId());
            }
        }
    }
}

std::vector<int> RoutingEfficiency::dijkstra(int source, int destination) {
    const auto& nodes = m_topologyManager->getNodes();
    const auto& links = m_topologyManager->getLinks();

    std::unordered_map<int, double> distance;
    std::unordered_map<int, int> previous;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    for (const auto& node : nodes) {
        distance[node->getId()] = std::numeric_limits<double>::infinity();
        previous[node->getId()] = -1;
    }

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == destination) break;

        for (const auto& link : links) {
            if (link->getSource().lock()->getId() == u || link->getTarget().lock()->getId() == u) {
                int v = (link->getSource().lock()->getId() == u) ? link->getTarget().lock()->getId() : link->getSource().lock()->getId();
                double weight = 1.0;  // Assume unit weight for simplicity

                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    previous[v] = u;
                    pq.push({distance[v], v});
                }
            }
        }
    }

    std::vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    return path;
}

double RoutingEfficiency::calculateRoutingOverhead() {
    // Simplified overhead calculation based on routing table size
    size_t totalEntries = 0;
    for (const auto& entry : m_routingTable) {
        totalEntries += entry.second.size();
    }
    return static_cast<double>(totalEntries) / m_topologyManager->getNodes().size();
}

double RoutingEfficiency::calculateAveragePathLength() {
    double totalLength = 0;
    int pathCount = 0;

    for (const auto& entry : m_routingTable) {
        totalLength += entry.second.size() - 1;  // Number of hops is path size - 1
        pathCount++;
    }

    return totalLength / pathCount;
}
