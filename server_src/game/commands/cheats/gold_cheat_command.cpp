#include "gold_cheat_command.h"

#include "../../entities/player.h"

void GoldCheatCommand::apply(Player &player, int amount) {
  player.setCoins(amount);
}