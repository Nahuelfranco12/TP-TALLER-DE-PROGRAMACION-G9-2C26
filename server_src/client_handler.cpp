#include "client_handler.h"

#include <string>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"

ClientHandler::ClientHandler(Socket&& skt, int client_id, Lobby& lobby):
        client_id(client_id),
        protocol(std::move(skt)),
        to_send_queue(QUEUE_MAX_SIZE),
        lobby(lobby),
        receiver(protocol, received_queue, client_id),
        sender(protocol, to_send_queue)
        {}

void ClientHandler::start() {
    protocol.send_player_id(client_id);
    receiver.start();
    sender.start();
}

bool ClientHandler::is_dead() {
    return !receiver.is_alive();
}

ClientHandler::~ClientHandler() {
    receiver.stop();
    sender.stop();
    to_send_queue.close();
    protocol.shutdown();
    receiver.join();
    sender.join();
}
