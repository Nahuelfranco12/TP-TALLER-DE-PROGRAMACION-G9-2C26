#ifndef JOIN_COMMAND_H_
#define JOIN_COMMAND_H_

#include "../command.h"
#include "../../server_src/game/id_sector.h"

class JoinCommand : public Command {
private:
    int playerId;

public:
    JoinCommand(int playerId) : playerId(playerId) {}

    void execute(World& world) override;
};

#endif // JOIN_COMMAND_H_