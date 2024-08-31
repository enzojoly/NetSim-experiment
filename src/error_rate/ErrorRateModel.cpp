#include "ErrorRateModel.h"
#include <cmath>
#include <algorithm>
#include <random>
#include "Packet.h" // Ensure this header includes the Packet class definition

ErrorRateModel::ErrorRateModel(double baseErrorRate)
    : m_baseErrorRate(baseErrorRate),
      m_signalToNoiseRatio(30.0), // Example default value
      m_interference(0.1),        // Example default value
      m_distance(100.0),          // Example default value
      m_generator(std::random_device{}()),
      m_distribution(0.0, 1.0) {}

std::vector<bool> ErrorRateModel::simulateErrors(const std::vector<Packet>& packets) {
    std::vector<bool> errors;
    errors.reserve(packets.size());

    for (const auto& packet : packets) {
        bool hasError = simulateBitErrors(packet) || simulateBurstErrors(packet) || simulatePacketLoss(packet);
        errors.push_back(hasError);
    }

    return errors;
}

void ErrorRateModel::updateEnvironmentalFactors(double signalToNoiseRatio, double interference, double distance) {
    m_signalToNoiseRatio = signalToNoiseRatio;
    m_interference = interference;
    m_distance = distance;
}

std::vector<Packet> ErrorRateModel::applyErrorCorrectionAndRetransmission(const std::vector<Packet>& packets, const std::vector<bool>& errors) {
    std::vector<Packet> correctedPackets;
    correctedPackets.reserve(packets.size());

    for (size_t i = 0; i < packets.size(); ++i) {
        if (errors[i]) {
            if (applyForwardErrorCorrection(packets[i])) {
                correctedPackets.push_back(packets[i]);
            } else {
                // Here you would typically retransmit or handle the packet loss
                // For simulation, we might just push back the original packet or a modified version
                correctedPackets.push_back(packets[i]);
            }
        } else {
            correctedPackets.push_back(packets[i]);
        }
    }

    return correctedPackets;
}

bool ErrorRateModel::simulateBitErrors(const Packet& packet) {
    double bitErrorRate = m_baseErrorRate * std::exp(-m_signalToNoiseRatio / 10.0);
    double packetErrorProbability = 1.0 - std::pow(1.0 - bitErrorRate, packet.getSize() * 8);
    return m_distribution(m_generator) < packetErrorProbability;
}

bool ErrorRateModel::simulateBurstErrors(const Packet& packet) {
    static const double burstProbability = 0.01;
    static const double burstErrorRate = 0.1;

    if (m_distribution(m_generator) < burstProbability) {
        double burstLength = std::min(static_cast<double>(packet.getSize()), std::exponential_distribution<>(50.0)(m_generator));
        double packetErrorProbability = 1.0 - std::pow(1.0 - burstErrorRate, burstLength * 8);
        return m_distribution(m_generator) < packetErrorProbability;
    }
    return false;
}

bool ErrorRateModel::simulatePacketLoss(const Packet& packet) {
    double packetLossProbability = 0.001 * (1.0 + m_interference) * std::log(m_distance);
    return m_distribution(m_generator) < packetLossProbability;
}

double ErrorRateModel::calculateErrorProbability() const {
    double distanceFactor = std::log(m_distance) / std::log(100.0);  // Normalize to 100m
    double interferenceFactor = 1.0 + m_interference;

    return 1.0 - std::exp(-m_baseErrorRate * distanceFactor * interferenceFactor * std::exp(-m_signalToNoiseRatio / 10.0));
}

bool ErrorRateModel::applyForwardErrorCorrection(const Packet& packet) {
    static const double fecCorrectionProbability = 0.8;
    return m_distribution(m_generator) < fecCorrectionProbability;
}

double ErrorRateModel::getCurrentErrorRate() const {
    // Implement or return a dummy value if not used
    return m_baseErrorRate; // This is a simple example
}
