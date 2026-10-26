#ifndef MOVE_COMMAND_H_
#define MOVE_COMMAND_H_

#include "../command.h"
#include "../position.h"

class MoveCommand : public Command {
private:
    int playerId;
    Position destination;

public:
    MoveCommand(int playerId, Position destination) : playerId(playerId), destination(destination) {}

    void execute(World& world) override;
};

#endif // MOVE_COMMAND_H_
