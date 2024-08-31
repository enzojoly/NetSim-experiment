#ifndef PACKET_H
#define PACKET_H

#include <cstdint>

class Packet {
public:
    enum class Priority { LOW, MEDIUM, HIGH };

    Packet(uint32_t id, Priority prio, uint32_t size, double time);
    Packet(double timestamp, uint32_t size);

    uint32_t getId() const { return id; }
    Priority getPriority() const { return priority; }
    void setPriority(Priority prio) { priority = prio; }
    uint32_t getSize() const { return size; }
    double getTimestamp() const { return timestamp; }

private:
    uint32_t id;
    Priority priority;
    uint32_t size;
    double timestamp;
};

#endif // PACKET_H

