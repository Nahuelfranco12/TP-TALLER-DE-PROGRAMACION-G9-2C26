#include "client_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <iostream>
#include <sys/socket.h>

#include "../common_src/constants.h"

ClientProtocol::ClientProtocol(const char* hostname, const char* servname):
        skt(hostname, servname), protocol(skt) {}

void ClientProtocol::send_msg(const std::string& msg) {
    protocol.send_string(msg);
}

std::string ClientProtocol::receive_msg() {
    return protocol.receive_string();
}

void ClientProtocol::shutdown() {
    try {
        skt.shutdown(SHUT_RDWR);
    } catch (const std::exception&) {}
}
