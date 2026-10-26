#ifndef MINE_COMMAND_H_
#define MINE_COMMAND_H_

#include "../command.h"
#include "../position.h"

class MineCommand : public Command {
private:
    int playerId;
    Position mineralPosition;

public:
    MineCommand(int playerId, Position mineralPosition) : playerId(playerId), mineralPosition(mineralPosition) {}

    void execute(World& world) override;
};

#endif // MINE_COMMAND_H_
