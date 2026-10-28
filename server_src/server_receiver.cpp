#include "server_receiver.h"

#include <stdexcept>
#include <iostream>

#include "../common_src/constants.h"
#include "./game/commands/move_command.h"
#include "./game/commands/leave_command.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Lobby& lobby, Queue<WorldState>& to_send_queue, int client_id):
    protocol(protocol), lobby(lobby), to_send_queue(to_send_queue), client_id(client_id) {}

void ServerReceiver::run() {
    try {
        // Logica para Unirse a partida.
        while(should_keep_running() && match == nullptr) {
            LobbyRequest request = protocol.receive_lobby_request();

            if(request.action == LobbyAction::Create) {
                protocol.send_match_created(lobby.create_match(request.text));
            } else if (request.action == LobbyAction::List) {
                protocol.send_match_list(lobby.list_matches());
            } else if (request.action == LobbyAction::Join) {
                Match* found = lobby.find_match(request.text);
                bool was_found = found != nullptr;
                protocol.send_join_result(was_found); // WARNING: revisar porque se manda el resultado antes de unirse/repercutir en la logica.
                if(was_found) {
                    match = found;
                    match->join(client_id, to_send_queue);
                }
            }
        }

        while(should_keep_running()) {
            // recibir peticion del cliente (del protocolo)
            // convertir a comando (con el factory)
            // pushear en el match (match->push_command(cmd))
            uint8_t op = protocol.receive_operation();
            switch (op) {
                case OP_MOVE:
                    break;
            }            
            
            // MoveDto move = protocol.receive_move();
            // MoveCommand move_cmd = MoveCommand(client_id, move.direction);
            // to_send_queue.push(&move_cmd);


        }
    } catch (const ClosedQueue&) {
        return;
    } catch (const std::exception&) {
        
    }

    try {
        to_send_queue.push(&LeaveCommand(client_id));
    } catch (const ClosedQueue&) {}

    protocol.shutdown();
}