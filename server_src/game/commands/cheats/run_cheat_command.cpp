#include "run_cheat_command.h"

#include "../../world.h"

void RunCheatCommand::execute(World &world) {
  Player *player = world.getPlayer(playerId);
  if (player)
    player->toggleRunCheat();
}