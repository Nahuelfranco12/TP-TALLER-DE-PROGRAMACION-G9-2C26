#ifndef MOVE_COMMAND_H_
#define MOVE_COMMAND_H_

#include "../command.h"
#include "../position.h"
#include "../../../common_src/game_dtos.h"

class MoveCommand : public Command {
private:
    int playerId;
    DirectionDto direction;

public:
    MoveCommand(int playerId, DirectionDto direction) : playerId(playerId), direction(direction) {}

    void execute(World& world) override;
};

#endif // MOVE_COMMAND_H_
