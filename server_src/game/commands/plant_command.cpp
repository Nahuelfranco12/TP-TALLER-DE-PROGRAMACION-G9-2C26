#include "plant_command.h"

#include <memory>

#include "../entities/crop.h"
#include "../world.h"

void PlantCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;

  Seed seed(PRICE_SEED, this->crop);
  if(player->getInventory().countOf(seed) == 0)
    return;

  if (!player->position.isAdjacentTo(this->target))
    return;

  Sector *sector = player->getActualSector();
  if (!sector)
    return;

  if (!sector->isTilled(this->target))
    return;

  if (sector->getEntity(this->target))
    return;

  if (!player->spendEnergy(ENERGY_COST_PLANT))
    return;

  std::unique_ptr<Entity> crop =
      std::make_unique<Crop>(this->target, this->crop);

  if (sector->tryAddEntity(crop, this->target))
    player->getInventory().remove(seed, 1);
}