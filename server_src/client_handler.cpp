#include "client_handler.h"

#include <string>
#include <utility>

#include <sys/socket.h>

#include "../common_src/constants.h"
#include "../common_src/liberror.h"

#include "./game/commands/join_command.h"

ClientHandler::ClientHandler(Socket&& skt, int client_id, Queue<Command*>& received_queue, ClientQueues& clients):
        client_id(client_id),
        protocol(std::move(skt)),
        to_send_queue(QUEUE_MAX_SIZE),
        received_queue(received_queue),
        clients(clients),
        receiver(protocol, received_queue, client_id),
        sender(protocol, to_send_queue)
        {}

void ClientHandler::start() {
    clients.add_client(client_id, to_send_queue);
    received_queue.push(&JoinCommand(client_id));
    receiver.start();
    sender.start();
}

bool ClientHandler::is_dead() {
    return !receiver.is_alive();
}

ClientHandler::~ClientHandler() {
    clients.remove_client(client_id);
    receiver.stop();
    sender.stop();
    to_send_queue.close();
    protocol.shutdown();
    receiver.join();
    sender.join();
    protocol.close();
}
