#include "client_handler.h"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"

ClientHandler::ClientHandler(Socket&& skt):
        protocol(std::move(skt)) {}

void ClientHandler::run() {
    protocol.receive_msg();
    protocol.send_msg();
}

ClientHandler::~ClientHandler() {
    stop();
    protocol.close();
    join();
}
