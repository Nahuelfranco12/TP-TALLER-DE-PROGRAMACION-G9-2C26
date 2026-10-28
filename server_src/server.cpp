#include "server.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "../common_src/constants.h"
#include "../common_src/socket.h"

#include "acceptor.h"
#include "match.h"

Server::Server(const char* servname):
        acceptor(servname,lobby) {}

void Server::run() {
    acceptor.start();

    char character;
    while (std::cin >> character && character != END_OP) {}
}
