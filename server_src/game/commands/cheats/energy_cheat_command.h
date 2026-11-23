#ifndef ENERGY_CHEAT_COMMAND_H_
#define ENERGY_CHEAT_COMMAND_H_

#include <string>

#include "amount_cheat_command.h"

class EnergyCheatCommand : public AmountCheatCommand {
protected:
  void apply(Player &player, int amount) override;

public:
  EnergyCheatCommand(int playerId, const std::string &args)
      : AmountCheatCommand(playerId, args) {}
};

#endif // ENERGY_CHEAT_COMMAND_H_