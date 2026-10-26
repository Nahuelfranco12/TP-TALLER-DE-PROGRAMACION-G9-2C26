#include "client_handler.h"

#include <string>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"

ClientHandler::ClientHandler(Socket&& skt, int client_id, Match& match):
        client_id(client_id),
        protocol(std::move(skt)),
        to_send_queue(QUEUE_MAX_SIZE),
        match(match),
        receiver(protocol, received_queue, client_id),
        sender(protocol, to_send_queue)
        {}

void ClientHandler::start() {
    match.join(client_id, to_send_queue);
    receiver.start();
    sender.start();
}

bool ClientHandler::is_dead() {
    return !receiver.is_alive();
}



ClientHandler::~ClientHandler() {
    match.leave(client_id);
    receiver.stop();
    sender.stop();
    to_send_queue.close();
    protocol.shutdown();
    receiver.join();
    sender.join();
    protocol.close();
}
