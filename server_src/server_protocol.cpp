#include "server_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <iostream>

#include <arpa/inet.h>

#include "../common_src/constants.h"

ServerProtocol::ServerProtocol(Socket&& socket): skt(std::move(socket)), protocol(skt) {}

void ServerProtocol::send_msg(const std::string& msg) {
    protocol.send_string(msg);
}
std::string ServerProtocol::receive_msg() {
    return protocol.receive_string();
}


void ServerProtocol::shutdown() {
    try {
        skt.shutdown(SHUT_RDWR);
    } catch (const std::exception&) {}
}

void ServerProtocol::close() {
    shutdown();
    try {
        skt.close();
    } catch (const std::exception&) {}
}
