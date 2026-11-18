#include "move_command.h"

void MoveCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;

  Position destination = player->position.next(this->direction);
  
  MoveResult moveRes = player->move(destination);
  if (moveRes.success && moveRes.idSector != player->getActualSector()->getId())
    player->setActualSector(world.getSector(moveRes.idSector));
}
