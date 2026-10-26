#ifndef LEAVE_COMMAND_H_
#define LEAVE_COMMAND_H_

#include "../command.h"
#include "../id_sector.h"

class LeaveCommand : public Command {
private:
    int playerId;

public:
    LeaveCommand(int playerId) : playerId(playerId) {}

    void execute(World& world) override;
};

#endif // LEAVE_COMMAND_H_
