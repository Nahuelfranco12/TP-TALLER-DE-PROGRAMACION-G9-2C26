#include "server_receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Queue<ClientCommand>& received_queue, int client_id):
    protocol(protocol), received_queue(received_queue), client_id(client_id) {}

void ServerReceiver::run() {
    try {
        while(should_keep_running()) {
            MoveCommand move = protocol.receive_move();
            received_queue.push(ClientCommand{client_id, CommandType::Move, move.direction});
            
        }
    } catch (const ClosedQueue&) {
        return;
    } catch (const std::exception&) {
        
    }

    try {
        received_queue.push(ClientCommand{client_id, CommandType::Leave});
    } catch (const ClosedQueue&) {}

    protocol.shutdown();
}