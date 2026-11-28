#include "move_command.h"

void MoveCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;
  
  if (moveRes.success && moveRes.idSector != player->getActualSector()->getId()) {
    IdSector oldSector = player->getActualSector()->getId();
    player->setActualSector(world.getSector(moveRes.idSector));
    if (oldSector != moveRes.idSector)
      player->resetCavernDamageFlag();
  }
}
