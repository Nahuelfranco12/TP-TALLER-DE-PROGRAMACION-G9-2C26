#ifndef COLLECT_COMMAND_H_
#define COLLECT_COMMAND_H_

#include "../../../common_src/game_dtos.h"
#include "../command.h"

class CollectCommand : public Command {
private:
    int playerId;
    DirectionDto direction;

public:
    CollectCommand(int playerId, DirectionDto direction)
        : playerId(playerId), direction(direction) {}

    void execute(World& world) override;
};

#endif // COLLECT_COMMAND_H_
