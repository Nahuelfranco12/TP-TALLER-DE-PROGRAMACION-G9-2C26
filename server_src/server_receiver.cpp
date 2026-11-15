#include "server_receiver.h"

#include <iostream>
#include <stdexcept>

#include "../common_src/constants.h"

ServerReceiver::ServerReceiver(ServerProtocol &protocol, Lobby &lobby,
                               Queue<WorldState> &to_send_queue, int client_id)
    : protocol(protocol), lobby(lobby), to_send_queue(to_send_queue),
      client_id(client_id) {}

void ServerReceiver::run() {
  try {
    // Logica para Unirse a partida.
    while (should_keep_running() && match == nullptr) {
      LobbyRequestDto request = protocol.receive_lobby_request();

      if (request.action == LobbyActionDto::Create) {
        protocol.send_match_created(lobby.create_match(request.match_name));
      } else if (request.action == LobbyActionDto::List) {
        protocol.send_match_list(lobby.list_matches());
      } else if (request.action == LobbyActionDto::Join) {
        Match *found = lobby.find_match(request.code);
        bool was_found = found != nullptr;
        protocol.send_join_result(
            was_found); // Se le avisa al cliente que se va a unir primero para
                        // que se prepare para recibir WorldStates
        if (was_found) {
          match = found;
          match->join(client_id, to_send_queue,
                      factory.create_join(client_id, request.player_name, request.player_outfit));
        }
      }
    }

    while (should_keep_running()) {
      // recibir peticion del cliente (del protocolo)
      // convertir a comando (con el factory)
      // pushear en el match (match->push_command(cmd))
      int op = protocol.receive_operation();
      switch (op) {
      case OP_MOVE:
        match->push_command(factory.create(client_id, protocol.receive_move()));
        break;
      case OP_SELECT_TOOL:
        match->push_command(
            factory.create(client_id, protocol.receive_select_tool()));
        break;
      case OP_MINE:
        match->push_command(factory.create(client_id, protocol.receive_mine()));
        break;
      case OP_COLLECT:
        match->push_command(
            factory.create(client_id, protocol.receive_collect()));
        break;
      case OP_PLANT:
        match->push_command(
            factory.create(client_id, protocol.receive_plant()));
        break;
      case OP_TILL:
        match->push_command(factory.create(client_id, protocol.receive_till()));
        break;
      case OP_WATER:
        match->push_command(
            factory.create(client_id, protocol.receive_water()));
        break;
      case OP_GIFT_OFFER:
        match->push_command(
            factory.create(client_id, protocol.receive_gift_offer()));
        break;
      case OP_GIFT_RESPONSE:
        match->push_command(
            factory.create(client_id, protocol.receive_gift_response()));
        break;
      case OP_ATTACK:
        match->push_command(
            factory.create(client_id, protocol.receive_attack()));
        break;
      case OP_CHEAT_WATER:
        match->push_command(factory.create_cheat_water(
            client_id, protocol.receive_cheat_water()));
        break;
      case OP_CHAT: {
        match->push_command(factory.create(client_id, protocol.receive_chat()));
        break;
      }
      case OP_CHEAT_GROWTH:
        match->push_command(factory.create_cheat_growth(client_id));
        break;
      default:
        throw std::runtime_error("Operación desconocida");
      }
    }
  } catch (const ClosedQueue &) {
  } catch (const std::exception &) {
  }

  if (match != nullptr) {
    match->leave(client_id);
  }

  protocol.shutdown();
}
