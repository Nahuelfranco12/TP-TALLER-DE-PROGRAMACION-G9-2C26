#include "water_command.h"

#include "../entities/waterable.h"
#include "../world.h"

void WaterCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;

  Tool *tool = player->getSelectedTool();
  if (!tool || tool->toolType != AvailableTools::WATERING_CAN)
    return;

  Position target(player->position.x, player->position.y);
  switch (this->direction) {
  case DirectionDto::Up:
    target.y -= 1;
    break;
  case DirectionDto::Down:
    target.y += 1;
    break;
  case DirectionDto::Left:
    target.x -= 1;
    break;
  case DirectionDto::Right:
    target.x += 1;
    break;
  }

  Sector *sector = player->getActualSector();
  if (!sector)
    return;

  Entity *entity = sector->getEntity(target);
  if (!entity)
    return;

  IWaterable *waterable = dynamic_cast<IWaterable *>(entity);
  if (!waterable || !waterable->needsWater())
    return;

  if (!player->spendEnergy(waterable->waterEnergyCost()))
    return;

  waterable->water();
}
