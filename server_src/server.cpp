#include "server.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "../common_src/constants.h"
#include "../common_src/socket.h"

#include "acceptor.h"

Server::Server(const char* servname):
        received_queue(QUEUE_MAX_SIZE), gameloop(received_queue, client_queues), acceptor(servname, received_queue, client_queues) {}

void Server::run() {
    gameloop.start();
    acceptor.start();

    char character;
    while (std::cin >> character && character != END_OP) {}

    received_queue.close();
    gameloop.stop();
    gameloop.join();
}
