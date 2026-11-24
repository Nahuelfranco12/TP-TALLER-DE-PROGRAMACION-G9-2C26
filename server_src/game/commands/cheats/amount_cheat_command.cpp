#include "amount_cheat_command.h"

#include "../../../../common_src/constants.h"
#include "../../world.h"

void AmountCheatCommand::execute(World &world) {
  Player *player = world.getPlayer(playerId);
  if (!player)
    return;

  int amount = 0;
  if (!readAmount(amount)) {
    world.addChat({SYSTEM_SENDER_ID, SYSTEM_SENDER_NAME, playerId, "Falta la cantidad"});
    return;
  }
  apply(*player, amount);
}

bool AmountCheatCommand::readAmount(int &amount) const {
  bool negative = !args.empty() && args[0] == '-';
  std::string digits = negative ? args.substr(1) : args;

  if (digits.empty() || digits.size() > 6)
    return false;
  for (char c : digits)
    if (c < '0' || c > '9')
      return false;

  amount = std::stoi(args);
  return true;
}