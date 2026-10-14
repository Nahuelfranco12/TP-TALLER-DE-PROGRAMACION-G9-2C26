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
    while (should_keep_running()) {
        std::optional<uint8_t> op = protocol.receive_operation();
        if (!op)
            break;

        auto it = commands.find(static_cast<operations>(*op));
        if (it != commands.end())
            it->second();
        else
            throw std::runtime_error(UNKNOWN_OP_ERROR);
    }
}

ClientHandler::~ClientHandler() {
    stop();
    protocol.close();
    join();
}
