#include "move_command.h"

void MoveCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;
  
  MoveResult moveRes = player->move(this->direction);
  if (moveRes.success && moveRes.idSector != player->getActualSector()->getId())
    player->setActualSector(world.getSector(moveRes.idSector));
}
