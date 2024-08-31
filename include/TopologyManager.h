#ifndef TOPOLOGY_MANAGER_H
#define TOPOLOGY_MANAGER_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <random>

class Node;
class Link;

class TopologyManager {
public:
    TopologyManager(int initialNodeCount);

    void generateInitialTopology();
    void simulateTopologyChanges(double duration);
    const std::vector<std::shared_ptr<Node>>& getNodes() const { return m_nodes; }
    const std::vector<std::shared_ptr<Link>>& getLinks() const { return m_links; }
    void addNode();
    void removeNode(int nodeId);
    void addLink(int sourceId, int targetId);
    void removeLink(int sourceId, int targetId);
    bool hasAnyFailure() const { return m_hasFailure; }

private:
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::vector<std::shared_ptr<Link>> m_links;
    std::mt19937 m_generator;
    bool m_hasFailure;

    void connectNodes(std::shared_ptr<Node> source, std::shared_ptr<Node> target);
    void disconnectNodes(std::shared_ptr<Node> source, std::shared_ptr<Node> target);
    std::shared_ptr<Node> findNodeById(int id);
    std::shared_ptr<Link> findLinkByNodes(int sourceId, int targetId);
};

class Node {
public:
    Node(int id) : m_id(id) {}
    int getId() const { return m_id; }
    const std::vector<std::weak_ptr<Link>>& getLinks() const { return m_links; }
    void addLink(std::weak_ptr<Link> link) { m_links.push_back(link); }
    void removeLink(std::weak_ptr<Link> link);

private:
    int m_id;
    std::vector<std::weak_ptr<Link>> m_links;
};

class Link {
public:
    Link(std::weak_ptr<Node> source, std::weak_ptr<Node> target)
        : m_source(source), m_target(target) {}
    std::weak_ptr<Node> getSource() const { return m_source; }
    std::weak_ptr<Node> getTarget() const { return m_target; }

private:
    std::weak_ptr<Node> m_source;
    std::weak_ptr<Node> m_target;
};

#endif // TOPOLOGY_MANAGER_H

