#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

#include "../common_src/game_dtos.h"

enum class CommandType { Join, Move, Leave };

struct ClientCommand {
    int client_id = 0;
    CommandType type = CommandType::Move;
    Direction direction  = Direction::Up; 
};

//to do: ver una forma de que los structs no tengan parametros innecesarios para todo comando (por ej, la direction)

#endif