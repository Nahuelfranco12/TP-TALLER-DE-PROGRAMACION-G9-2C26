#include "server.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "../common_src/constants.h"
#include "../common_src/socket.h"

#include "acceptor.h"

Server::Server(const char* servname, Game& game):
        servname(servname), game(game), acceptor(servname, game) {}

void Server::run() {
    acceptor.start();

    while (std::cin.get() != END_OP) {}
}
