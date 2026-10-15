#include "client_handler.h"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"

namespace {
    constexpr unsigned int QUEUE_MAX_SIZE = 1000;
}

ClientHandler::ClientHandler(Socket&& skt):
        protocol(std::move(skt)),
        queue(QUEUE_MAX_SIZE),
        receiver(protocol, queue),
        sender(protocol, queue) {}

void ClientHandler::start() {
    receiver.start();
    sender.start();
}

bool ClientHandler::is_dead() {
    return !receiver.is_alive() && !sender.is_alive();
}



ClientHandler::~ClientHandler() {
    receiver.stop();
    sender.stop();

    try{
        queue.close();
    } catch(const std::exception&) {

    }
    protocol.shutdown();

    receiver.join();
    sender.join();
    
    protocol.close();
}
