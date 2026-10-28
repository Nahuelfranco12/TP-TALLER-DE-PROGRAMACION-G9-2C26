#include "server_receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Lobby& lobby, Queue<WorldState>& to_send_queue, int client_id):
    protocol(protocol), lobby(lobby), to_send_queue(to_send_queue), client_id(client_id) {}

void ServerReceiver::run() {
    try {
        while(should_keep_running() && match == nullptr) {
            LobbyRequest request = protocol.receive_lobby_request();

            if(request.action == LobbyAction::Create) {
                protocol.send_match_created(lobby.create_match(request.text));
            } else if (request.action == LobbyAction::List) {
                protocol.send_match_list(lobby.list_matches());
            } else if (request.action == LobbyAction::Join) {
                Match* found == lobby.find_match(request.text);
                bool was_found = found != nullptr;
                protocol.send_join_result(was_found);
                if(was_found) {
                    found->join(client_id, to_send_queue);
                    match = found;
                }
            }
        }
    }

    try {
        while(should_keep_running()) {
            MoveCommand move = protocol.receive_move();
            match.push_command(ClientCommand{client_id, CommandType::Move, move.direction});
            
        }
    } catch (const ClosedQueue&) {
        return;
    } catch (const std::exception&) {
        
    }

    if(match != nullptr)
        match->leave(client_id);
    protocol.shutdown();
}