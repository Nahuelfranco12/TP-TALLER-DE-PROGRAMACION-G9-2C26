#ifndef RUN_CHEAT_COMMAND_H_
#define RUN_CHEAT_COMMAND_H_

#include "../../command.h"

class RunCheatCommand : public Command {
private:
  int playerId;

public:
  explicit RunCheatCommand(int playerId) : playerId(playerId) {}

  void execute(World &world) override;
};

#endif // RUN_CHEAT_COMMAND_H_