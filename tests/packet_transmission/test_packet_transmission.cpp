//#include <gtest/gtest.h> //googletest header file
#include "../../src/packet_transmission/PacketTransmissionSimulator.h"

TEST(PacketTransmissionTest, BasicTransmission) {
    auto packets = simulatePacketTransmission(10, 100);
    ASSERT_EQ(packets.size(), 100);  // Example assertion
}
