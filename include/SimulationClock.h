#ifndef SIMULATION_CLOCK_H
#define SIMULATION_CLOCK_H

#include <chrono>
#include <atomic>
#include <memory>

class SimulationClock {
public:
    static SimulationClock& getInstance();

    void start();
    void stop();
    double getCurrentTime() const;
    void advanceTime(double duration);

    SimulationClock(const SimulationClock&) = delete;
    SimulationClock& operator=(const SimulationClock&) = delete;

private:
    SimulationClock();  // Private constructor

    std::chrono::steady_clock::time_point m_startTime;
    std::atomic<double> m_simTime;
    std::atomic<bool> m_running;
};

#endif // SIMULATION_CLOCK_H

