#include "place_command.h"

#include <memory>

#include "../inventory/placeable.h"
#include "../world.h"

void PlaceCommand::execute(World &world) {
  Player *player = world.getPlayer(playerId);
  if (!player)
    return;

  Sector *sector = player->getActualSector();
  if (!sector)
    return;

  Position target(player->position.x, player->position.y);
  switch (this->direction) {
  case DirectionDto::Up:
    target.y = player->position.y - 1;
    break;
  case DirectionDto::Down:
    target.y = player->position.y + 1;
    break;
  case DirectionDto::Left:
    target.x = player->position.x - 1;
    break;
  case DirectionDto::Right:
    target.x = player->position.x + 1;
    break;
  }

  if (!sector->isEmpty(target))
    return;

  const Item *item = player->getInventory().itemAt(slotIndex);
  const auto *placeable = dynamic_cast<const Placeable *>(item);
  if (!placeable || !placeable->canBePlacedAt(*sector, target))
    return;

  std::unique_ptr<Entity> entity = placeable->toEntity(target);
  if (sector->tryAddEntity(entity, target))
    player->getInventory().removeFromSlot(slotIndex);
}