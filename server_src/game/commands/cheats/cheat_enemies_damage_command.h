#ifndef CHEAT_ENEMIES_DAMAGE_H_COMMAND_H_
#define CHEAT_ENEMIES_DAMAGE_H_COMMAND_H_

#include "../../../../common_src/game_dtos.h"
#include "../../command.h"

class CheatEnemiesDamageCommand : public Command {
private:
  int playerId;

public:
  CheatEnemiesDamageCommand(int playerId) : playerId(playerId) {}

  void execute(World &world) override;
};

#endif // CHEAT_ENEMIES_DAMAGE_H_COMMAND_H_
