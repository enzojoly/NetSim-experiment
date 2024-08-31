#include "SimulationClock.h"
#include <atomic>

SimulationClock& SimulationClock::getInstance() {
    static SimulationClock instance;
    return instance;
}

SimulationClock::SimulationClock() : m_simTime(0), m_running(false) {}

void SimulationClock::start() {
    m_startTime = std::chrono::steady_clock::now();
    m_simTime = 0;
    m_running = true;
}

void SimulationClock::stop() {
    m_running = false;
}

double SimulationClock::getCurrentTime() const {
    if (m_running) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = now - m_startTime;
        return m_simTime + diff.count();
    }
    return m_simTime;
}

void SimulationClock::advanceTime(double duration) {
    if (m_running) {
        double current = m_simTime.load();
        while (!m_simTime.compare_exchange_weak(current, current + duration)) {
            // If compare_exchange_weak fails, it updates current with the latest value,
            // so we just try again in this loop.
        }
    }
}
