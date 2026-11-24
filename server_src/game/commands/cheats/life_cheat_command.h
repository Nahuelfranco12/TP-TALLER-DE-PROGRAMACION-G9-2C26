#ifndef LIFE_CHEAT_COMMAND_H_
#define LIFE_CHEAT_COMMAND_H_

#include <string>

#include "amount_cheat_command.h"

class LifeCheatCommand : public AmountCheatCommand {
protected:
  void apply(Player &player, int amount) override;

public:
  LifeCheatCommand(int playerId, const std::string &args)
      : AmountCheatCommand(playerId, args) {}
};

#endif // LIFE_CHEAT_COMMAND_H_