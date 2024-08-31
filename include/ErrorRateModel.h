#ifndef ERROR_RATE_MODEL_H
#define ERROR_RATE_MODEL_H

#include <vector>
#include <random>
#include "Packet.h" // Assuming Packet.h exists with Packet class definition

class ErrorRateModel {
public:
    ErrorRateModel(double baseErrorRate);

    std::vector<bool> simulateErrors(const std::vector<Packet>& packets);
    void updateEnvironmentalFactors(double signalToNoiseRatio, double interference, double distance);
    std::vector<Packet> applyErrorCorrectionAndRetransmission(const std::vector<Packet>& packets, const std::vector<bool>& errors);
    double calculateErrorProbability() const;
    double getCurrentErrorRate() const;

private:
    double m_baseErrorRate;
    double m_signalToNoiseRatio;
    double m_interference;
    double m_distance;
    std::mt19937 m_generator;
    std::uniform_real_distribution<> m_distribution;

    bool simulateBitErrors(const Packet& packet);
    bool simulateBurstErrors(const Packet& packet);
    bool simulatePacketLoss(const Packet& packet);
    bool applyForwardErrorCorrection(const Packet& packet);
};

#endif // ERROR_RATE_MODEL_H

