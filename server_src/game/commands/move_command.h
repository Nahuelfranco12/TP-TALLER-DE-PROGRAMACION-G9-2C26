#ifndef MOVE_COMMAND_H_
#define MOVE_COMMAND_H_

#include "../command.h"
#include "../id_player.h"
#include "../position.h"

class MoveCommand : public Command {
private:
    IdPlayer playerId;
    Position destination;

public:
    MoveCommand(IdPlayer playerId, Position destination) : playerId(playerId), destination(destination) {}

    void execute(World& world) override;
};

#endif // MOVE_COMMAND_H_
