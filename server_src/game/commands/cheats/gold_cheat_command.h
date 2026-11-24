#ifndef GOLD_CHEAT_COMMAND_H_
#define GOLD_CHEAT_COMMAND_H_

#include <string>

#include "amount_cheat_command.h"

class GoldCheatCommand : public AmountCheatCommand {
protected:
  void apply(Player &player, int amount) override;

public:
  GoldCheatCommand(int playerId, const std::string &args)
      : AmountCheatCommand(playerId, args) {}
};

#endif // GOLD_CHEAT_COMMAND_H_