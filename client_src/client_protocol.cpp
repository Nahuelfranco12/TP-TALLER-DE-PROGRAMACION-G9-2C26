#include "client_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <iostream>

#include "../common_src/constants.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* servname):
        skt(hostname, servname), protocol(skt) {}

void ClientProtocol::send_msg() {
    protocol.send_string("Hola Mundo");
}

void ClientProtocol::receive_msg() {
    std::string received_msg = protocol.receive_string();
    std::cout << received_msg;
}
