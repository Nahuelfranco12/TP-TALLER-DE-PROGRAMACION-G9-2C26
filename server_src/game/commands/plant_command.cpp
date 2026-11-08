#include "plant_command.h"

#include <memory>

#include "../entities/crop.h"
#include "../world.h"

void PlantCommand::execute(World &world) {
    Player *player = world.getPlayer(this->playerId);
    if(!player) 
        return;
    
    if (!player->position.isAdjacentTo(this->target)) return;

    Sector *sector = player->getActualSector();
    if (!sector) return;

    if (sector->getEntity(this->target)) return;

    // todo: chequear q la casilla sea arable y tenga la semilla (y gastarla)

    sector->addEntity(std::make_unique<Crop>(this->target, this->crop), this->target);
}