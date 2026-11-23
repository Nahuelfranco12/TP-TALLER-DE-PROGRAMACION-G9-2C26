#include "energy_cheat_command.h"

#include "../../entities/player.h"

void EnergyCheatCommand::apply(Player &player, int amount) {
  player.setEnergy(amount);
}