#include "life_cheat_command.h"

#include "../../entities/player.h"

void LifeCheatCommand::apply(Player &player, int amount) {
  player.setLife(amount);
}