#include "interact_command.h"

#include <cstdlib>

#include "../entities/interactable.h"
#include "../world.h"

void InteractCommand::execute(World &world) {
    Player *player = world.getPlayer(playerId);
    if (!player)
        return;
    
    if(player->position.distanceTo(target) > INTERACT_DISTANCE)
        return;
    
    Entity *entity = player->getActualSector()->getEntity(target);
    auto *interactable = dynamic_cast<Interactable *>(entity);
    if (interactable)
        interactable->interact(world, *player);
}