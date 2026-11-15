#ifndef CHEAT_GROWTH_H_COMMAND_H_
#define CHEAT_GROWTH_H_COMMAND_H_

#include "../../../../common_src/game_dtos.h"
#include "../../command.h"

class CheatGrowthCommand : public Command {
private:
  int playerId;

public:
  CheatGrowthCommand(int playerId) : playerId(playerId) {}

  void execute(World &world) override;
};

#endif // CHEAT_GROWTH_H_COMMAND_H_
