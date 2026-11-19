#include "plant_command.h"

#include <memory>

#include "../entities/crop.h"
#include "../world.h"

void PlantCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
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

  // todo: chequear q la casilla sea arable y tenga la semilla (y gastarla)

  if (!player->spendEnergy(ENERGY_COST_PLANT))
    return;

  std::unique_ptr<Entity> crop =
      std::make_unique<Crop>(this->target, this->crop);
  sector->tryAddEntity(crop, this->target);
}