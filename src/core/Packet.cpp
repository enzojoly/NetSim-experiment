#include "Packet.h"

Packet::Packet(uint32_t id, Priority prio, uint32_t size, double time)
    : id(id), priority(prio), size(size), timestamp(time) {}

Packet::Packet(double timestamp, uint32_t size)
    : id(0), priority(Priority::MEDIUM), size(size), timestamp(timestamp) {}
