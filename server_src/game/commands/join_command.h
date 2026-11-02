#ifndef JOIN_COMMAND_H_
#define JOIN_COMMAND_H_

#include "../command.h"
#include "../game_constants.h"

class JoinCommand : public Command {
private:
    int playerId;
    PlayerOutfit outfit;

public:
    JoinCommand(int playerId, PlayerOutfit outfit) : playerId(playerId), outfit(outfit) {}

    void execute(World& world) override;
};

#endif // JOIN_COMMAND_H_
