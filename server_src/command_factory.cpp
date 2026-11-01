#include "command_factory.h"

std::unique_ptr<Command> CommandFactory::create(int player_id, const MoveDto& dto) {
    return std::make_unique<MoveCommand>(player_id, dto.direction);
}

