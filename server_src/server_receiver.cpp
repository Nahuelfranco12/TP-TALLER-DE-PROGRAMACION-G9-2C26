#include "server_receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"
#include "./game/commands/leave_command.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Queue<Command*>& received_queue, int client_id):
    protocol(protocol), received_queue(received_queue), client_id(client_id) {}

void ServerReceiver::run() {
    try {
        while(should_keep_running()) {
            MoveCommand move = protocol.receive_move();
            received_queue.push(&move);
        }
    } catch (const ClosedQueue&) {
        return;
    } catch (const std::exception&) {
        
    }

    try {
        received_queue.push(&LeaveCommand(client_id));
    } catch (const ClosedQueue&) {}

    protocol.shutdown();
}