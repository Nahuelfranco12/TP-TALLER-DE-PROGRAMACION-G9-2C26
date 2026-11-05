#include "move_command.h"

void MoveCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;

  Position destination(player->position.x, player->position.y);
  switch (this->direction) {
  case DirectionDto::Up:
    destination.y = player->position.y - 1;
    break;
  case DirectionDto::Down:
    destination.y = player->position.y + 1;
    break;
  case DirectionDto::Left:
    destination.x = player->position.x - 1;
    break;
  case DirectionDto::Right:
    destination.x = player->position.x + 1;
    break;
  }
  
  MoveResult moveRes = player->move(destination);
  if (moveRes.success && moveRes.idSector != player->getActualSector()->getId())
    player->setActualSector(world.getSector(moveRes.idSector));
}
