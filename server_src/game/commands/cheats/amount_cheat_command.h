#ifndef AMOUNT_CHEAT_COMMAND_H
#define AMOUNT_CHEAT_COMMAND_H

#include <string>

#include "../../command.h"
#include "../../entities/player.h"

class AmountCheatCommand : public Command {
  int playerId;
  std::string args;

  bool readAmount(int &amount) const;

protected:
  virtual void apply(Player &player, int amount) = 0;

public:
  AmountCheatCommand(int playerId, const std::string &args)
      : playerId(playerId), args(args) {}
  void execute(World &world) override;
};

#endif