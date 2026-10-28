#include "acceptor.h"

#include <iostream>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"

Acceptor::Acceptor(const char* servname, Lobby& lobby): 
        skt(servname), lobby(lobby) {}

void Acceptor::reap_dead() {
    clients.remove_if([](const std::unique_ptr<ClientHandler>& c) {
        return c->is_dead();
    });
}

void Acceptor::run() {
    while (should_keep_running()) {
        try {
            Socket peer = skt.accept();

            auto handler = std::make_unique<ClientHandler>(std::move(peer), next_client_id, lobby);
            next_client_id++;
            handler->start();

            reap_dead();
            clients.push_back(std::move(handler));
        } catch (const std::exception& e) {
            if (should_keep_running())
                std::cerr << e.what() << STRING_BRK;
            break;
        }
    }
}

Acceptor::~Acceptor() {
    stop();

    try {
        skt.shutdown(SHUT_RDWR);
    } catch (const std::exception&) {}
    try {
        skt.close();
    } catch (const std::exception&) {}

    join();
}
