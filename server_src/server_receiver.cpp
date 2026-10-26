#include "server_receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Match& match, int client_id):
    protocol(protocol), match(match), client_id(client_id) {}

void ServerReceiver::run() {
    try {
        while(should_keep_running()) {
            MoveCommand move = protocol.receive_move();
            match.push_command(ClientCommand{client_id, CommandType::Move, move.direction});
            
        }
    } catch (const ClosedQueue&) {
        return;
    } catch (const std::exception&) {
        
    }
    protocol.shutdown();
}