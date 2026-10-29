#include "client.h"

#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "../common_src/constants.h"
#include "actions/move_action.h"

Client::Client(const char* hostname, const char* servname):
        protocol(hostname, servname),
        my_id(protocol.receive_player_id()),
        received_queue(QUEUE_MAX_SIZE),
        to_send_queue(QUEUE_MAX_SIZE),
        receiver(protocol, received_queue),
        sender(protocol, to_send_queue)
        {}

// igual este run es de prueba, hay q sacarlo conectandolo con sdl
void Client::run() {
    std::string line;

    // TEST POR CONSOLA PARA LA PARTE DE QT (MENU)
    while (!in_game && std::getline(std::cin, line)) {
        if (line.rfind("c ", 0) == 0) {
            std::cout << "Partida creada, código: " << create_match(line.substr(2)) << STRING_BRK;
        } else if (line == "l") {
            for (const MatchInfoDto& m : list_matches())
                std::cout << m.code << " - " << m.name << " (" << m.players << " jugadores)"
                          << STRING_BRK;
        } else if (line.rfind("j ", 0) == 0) {
            if (join_match(line.substr(2)))
                std::cout << "Te uniste. Sos el jugador " << my_id << STRING_BRK;
            else
                std::cout << "No existe esa partida" << STRING_BRK;
        } else if (line == "q") {
            return;
        }
    }
    WorldStateDto state;

    // TEST POR CONSOLA DEL MOVIMIENTO DE LOS JUGADORES
    while(std::getline(std::cin, line) && line != "q") {
        if(!is_connected()) {
            break;
        }
        
        if(line == "w")
            send_move(DirectionDto::Up);
        else if(line == "s")
            send_move(DirectionDto::Down);
        else if(line == "a")
            send_move(DirectionDto::Left);
        else if(line == "d")
            send_move(DirectionDto::Right);

        if(try_get_latest_state(state)) {
            for(const PlayerPositionDto& p : state.players) {
                std::string mensaje = "Jugador " + std::to_string(p.id) + " en: " + std::to_string(p.x) + ", " + std::to_string(p.y) + STRING_BRK;
                std::cout << mensaje;
            }
        }
    }
}

// Métodos de acciones

void Client::send_move(DirectionDto direction) {
    to_send_queue.try_push(std::make_unique<MoveAction>(direction));
}


bool Client::try_get_latest_state(WorldStateDto& state){
    bool has_been_received = false;
    WorldStateDto next_state;
    while(received_queue.try_pop(next_state)){
        state = std::move(next_state);
        has_been_received = true;
    }
    return has_been_received;
}

bool Client::is_connected() const {
    return receiver.is_alive();
}

Client::~Client() {
    receiver.stop();
    sender.stop();
    to_send_queue.close();
    received_queue.close();
    protocol.shutdown();
    if(in_game) {
        receiver.join();
        sender.join();
    }
}

// Métodos de menú (QT)

std::string Client::create_match(const std::string& name) {
    protocol.send_create_match(name);
    return protocol.receive_created_match();
}
std::vector<MatchInfo> Client::list_matches() {
    protocol.send_list_matches();
    return protocol.receive_match_list();
}
bool Client::join_match(const std::string& code) {
    protocol.send_join_match(code);
    bool client_could_join = protocol.receive_join_result();
    if(client_could_join) {
        receiver.start();
        sender.start();
        in_game = true;
    }
    return client_could_join;
}

