#ifndef LEAVE_COMMAND_H_
#define LEAVE_COMMAND_H_

#include "../command.h"
#include "../game_constants.h"

class LeaveCommand : public Command {
private:
  int playerId;

public:
  explicit LeaveCommand(int playerId) : playerId(playerId) {}

  void execute(World &world) override;
};

#endif // LEAVE_COMMAND_H_
