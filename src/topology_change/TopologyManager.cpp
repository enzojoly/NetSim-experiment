#include "TopologyManager.h"
#include "SimulationClock.h"
#include <algorithm>
#include <stdexcept>

TopologyManager::TopologyManager(int initialNodeCount)
    : m_generator(std::random_device{}()) {
    for (int i = 0; i < initialNodeCount; ++i) {
        m_nodes.push_back(std::make_shared<Node>(i));
    }
}

void TopologyManager::generateInitialTopology() {
    // Implement a simple mesh topology for initial setup
    for (size_t i = 0; i < m_nodes.size(); ++i) {
        for (size_t j = i + 1; j < m_nodes.size(); ++j) {
            connectNodes(m_nodes[i], m_nodes[j]);
        }
    }
}

void TopologyManager::simulateTopologyChanges(double duration) {
    std::uniform_real_distribution<> timeDist(0, duration);
    std::uniform_int_distribution<> actionDist(0, 3);  // 0: add node, 1: remove node, 2: add link, 3: remove link

    int changes = static_cast<int>(duration / 10);  // One change every 10 time units on average

    for (int i = 0; i < changes; ++i) {
        double changeTime = timeDist(m_generator);
        SimulationClock::getInstance().advanceTime(changeTime);

        int action = actionDist(m_generator);
        switch (action) {
            case 0: addNode(); break;
            case 1: {
                if (!m_nodes.empty()) {
                    std::uniform_int_distribution<> nodeDist(0, m_nodes.size() - 1);
                    removeNode(m_nodes[nodeDist(m_generator)]->getId());
                }
                break;
            }
            case 2: {
                if (m_nodes.size() >= 2) {
                    std::uniform_int_distribution<> nodeDist(0, m_nodes.size() - 1);
                    int sourceId = m_nodes[nodeDist(m_generator)]->getId();
                    int targetId = m_nodes[nodeDist(m_generator)]->getId();
                    if (sourceId != targetId) {
                        addLink(sourceId, targetId);
                    }
                }
                break;
            }
            case 3: {
                if (!m_links.empty()) {
                    std::uniform_int_distribution<> linkDist(0, m_links.size() - 1);
                    auto link = m_links[linkDist(m_generator)];
                    removeLink(link->getSource().lock()->getId(), link->getTarget().lock()->getId());
                }
                break;
            }
        }
    }
}

void TopologyManager::addNode() {
    int newId = m_nodes.size();
    auto newNode = std::make_shared<Node>(newId);
    m_nodes.push_back(newNode);

    // Connect to a random existing node
    if (m_nodes.size() > 1) {
        std::uniform_int_distribution<> nodeDist(0, m_nodes.size() - 2);
        connectNodes(newNode, m_nodes[nodeDist(m_generator)]);
    }
}

void TopologyManager::removeNode(int nodeId) {
    auto nodeIt = std::find_if(m_nodes.begin(), m_nodes.end(),
                               [nodeId](const auto& node) { return node->getId() == nodeId; });
    if (nodeIt != m_nodes.end()) {
        auto node = *nodeIt;
        // Remove all links connected to this node
        m_links.erase(std::remove_if(m_links.begin(), m_links.end(),
            [node](const auto& link) {
                return link->getSource().lock() == node || link->getTarget().lock() == node;
            }), m_links.end());
        m_nodes.erase(nodeIt);
    }
}

void TopologyManager::addLink(int sourceId, int targetId) {
    auto source = findNodeById(sourceId);
    auto target = findNodeById(targetId);
    if (source && target) {
        connectNodes(source, target);
    }
}

void TopologyManager::removeLink(int sourceId, int targetId) {
    auto link = findLinkByNodes(sourceId, targetId);
    if (link) {
        auto source = link->getSource().lock();
        auto target = link->getTarget().lock();
        if (source && target) {
            disconnectNodes(source, target);
        }
    }
}

void TopologyManager::connectNodes(std::shared_ptr<Node> source, std::shared_ptr<Node> target) {
    auto link = std::make_shared<Link>(source, target);
    m_links.push_back(link);
    source->addLink(link);
    target->addLink(link);
}

void TopologyManager::disconnectNodes(std::shared_ptr<Node> source, std::shared_ptr<Node> target) {
    m_links.erase(std::remove_if(m_links.begin(), m_links.end(),
        [source, target](const auto& link) {
            return (link->getSource().lock() == source && link->getTarget().lock() == target) ||
                   (link->getSource().lock() == target && link->getTarget().lock() == source);
        }), m_links.end());
    source->removeLink(std::weak_ptr<Link>());
    target->removeLink(std::weak_ptr<Link>());
}

std::shared_ptr<Node> TopologyManager::findNodeById(int id) {
    auto it = std::find_if(m_nodes.begin(), m_nodes.end(),
                           [id](const auto& node) { return node->getId() == id; });
    return (it != m_nodes.end()) ? *it : nullptr;
}

std::shared_ptr<Link> TopologyManager::findLinkByNodes(int sourceId, int targetId) {
    auto it = std::find_if(m_links.begin(), m_links.end(),
        [sourceId, targetId](const auto& link) {
            auto source = link->getSource().lock();
            auto target = link->getTarget().lock();
            return (source && target) &&
                   ((source->getId() == sourceId && target->getId() == targetId) ||
                    (source->getId() == targetId && target->getId() == sourceId));
        });
    return (it != m_links.end()) ? *it : nullptr;
}

void Node::removeLink(std::weak_ptr<Link> link) {
    m_links.erase(std::remove_if(m_links.begin(), m_links.end(),
        [&link](const auto& l) { return l.lock() == link.lock(); }), m_links.end());
}
