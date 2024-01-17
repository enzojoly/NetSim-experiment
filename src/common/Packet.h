// Packet.h
#ifndef PACKET_H
#define PACKET_H

struct Packet {
    int type;  // Type of the packet (0 for normal, 1 for high priority)
    int size;  // Size of the packet in bytes

    // Constructor for creating a Packet
    Packet(int t, int s) : type(t), size(s) {}
};

#endif // PACKET_H

