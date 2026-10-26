#ifndef MINE_COMMAND_H_
#define MINE_COMMAND_H_

#include "../command.h"
#include "../id_player.h"
#include "../position.h"

class MineCommand : public Command {
private:
    IdPlayer playerId;
    Position mineralPosition;

public:
    MineCommand(IdPlayer playerId, Position mineralPosition) : playerId(playerId), mineralPosition(mineralPosition) {}

    void execute(World& world) override;
};

#endif // MINE_COMMAND_H_
