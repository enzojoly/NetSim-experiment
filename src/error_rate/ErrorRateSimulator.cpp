//Simulating the error rate in a network based on various factors like signal quality.

#include "ErrorRateSimulator.h"
#include <iostream>
#include <random>

// Function to simulate network error rate
double simulateErrorRate(double signalNoiseRatio) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(signalNoiseRatio, 5.0);

    return 1 / d(gen);

    signalNoiseRatio = 30.0; // Signal-to-Noise Ratio
    double errorRate = simulateErrorRate(signalNoiseRatio);
    std::cout << "Network Error Rate: " << errorRate << "\n";
    return 0;
}
