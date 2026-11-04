#include "mine_command.h"

#include "../entities/mineral.h"

void MineCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;

  // cppcheck-suppress constVariablePointer
  Sector *sector = player->getActualSector();
  if (!sector)
    return;

  Position targetPos(player->position.x, player->position.y);
  switch (this->direction) {
  case DirectionDto::Up:
    targetPos.y = player->position.y - 1;
    break;
  case DirectionDto::Down:
    targetPos.y = player->position.y + 1;
    break;
  case DirectionDto::Left:
    targetPos.x = player->position.x - 1;
    break;
  case DirectionDto::Right:
    targetPos.x = player->position.x + 1;
    break;
  }

  Entity *entity = sector->getEntity(targetPos);
  if (!entity)
    return;

  Mineral *mineral = dynamic_cast<Mineral *>(entity);
  if (!mineral)
    return;

  player->mine(*mineral);
}
