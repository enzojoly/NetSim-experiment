// Utils.h
#ifndef UTILS_H
#define UTILS_H

//#include <iostream> // for cout
// if uncommented: for utility functions like printPackets, this approach is typically safe as long as you don't include Utils.h in multiple compiled sources
#include <vector>
#include "Packet.h"

// Utility function to print the details of packets
void printPackets(const std::vector<Packet>& packets) {
    for (const auto& packet : packets) {
        std::cout << "Packet Type: " << packet.type << ", Size: " << packet.size << " bytes\n";
    }
}

#endif // UTILS_H

