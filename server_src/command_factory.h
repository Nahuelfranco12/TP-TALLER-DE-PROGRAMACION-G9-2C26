#ifndef COMMAND_FACTORY_H_
#define COMMAND_FACTORY_H_

#include "./game/command.h"
#include "../common_src/game_dtos.h"
#include "./game/commands/move_command.h"

class CommandFactory {
public:
    std::unique_ptr<Command> create(int player_id, const MoveDto& dto);
    std::unique_ptr<Command> create(int player_id, const MineDto& dto);
};

#endif // COMMAND_FACTORY_H_
