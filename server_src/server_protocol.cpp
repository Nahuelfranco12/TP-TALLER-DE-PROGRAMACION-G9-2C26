#include "server_protocol.h"

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <iostream>

#include <arpa/inet.h>

#include "../common_src/constants.h"

ServerProtocol::ServerProtocol(Socket&& socket): skt(std::move(socket)), protocol(skt) {}

void ServerProtocol::send_msg() {
    protocol.send_string("Chau Mundo");
}
void ServerProtocol::receive_msg() {
    std::string received_msg = protocol.receive_string();
    std::cout << received_msg;
}


void ServerProtocol::close() {
    try {
        skt.shutdown(SHUT_RDWR);
    } catch (const std::exception&) {}
    try {
        skt.close();
    } catch (const std::exception&) {}
}
