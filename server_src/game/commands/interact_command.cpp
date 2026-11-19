#include "interact_command.h"

#include <cstdlib>

#include "../entities/interactable.h"
#include "../world.h"

void InteractCommand::execute(World &world) {
    Player *player = world.getPlayer(playerId);
    if (!player)
        return;
    
    int distanceX = std::abs(static_cast<int>(player->position.x) - static_cast<int>(target.x));
    int distanceY = std::abs(static_cast<int>(player->position.y) - static_cast<int>(target.y));
    if (distanceX + distanceY > INTERACT_DISTANCE)
        return;
    
    Entity *entity = player->getActualSector()->getEntity(target);
    auto *interactable = dynamic_cast<Interactable *>(entity);
    if (interactable)
        interactable->interact(world, *player);
}