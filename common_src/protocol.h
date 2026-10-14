#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <cstdint>
#include <string>

#include "socket.h"

class Protocol {
private:
    Socket& skt;

public:
    explicit Protocol(Socket& skt);

    void send_u8(uint8_t value);
    void send_u16(uint16_t value);

    uint8_t receive_u8();
    uint16_t receive_u16();

    std::string receive_string();
    void send_string(const std::string& str);
};

#endif  // PROTOCOL_H_
