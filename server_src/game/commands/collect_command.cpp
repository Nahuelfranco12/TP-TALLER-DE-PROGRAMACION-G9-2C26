#include "collect_command.h"

#include "../entities/collectable.h"
#include "../world.h"

#include <utility>

void CollectCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
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

  ICollectable *collectable = dynamic_cast<ICollectable *>(entity);
  if (!collectable || !collectable->canCollect())
    return;

  if (!player->spendEnergy(collectable->energyCost()))
    return;

  bool should_remove = collectable->removeOnCollect();

  auto product = collectable->collect();
  player->getInventory().addItem(std::move(product));

  if (should_remove) {
    sector->removeEntity(target);
  }
}
