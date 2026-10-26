#include "mine_command.h"
#include "../entities/mineral.h"
#include "../world.h"

void MineCommand::execute(World& world) {
    Player* player = world.getPlayer(this->playerId);
    if (!player)
        return;

    Sector* sector = player->getActualSector();
    if (!sector)
        return;

    Entity* entity = sector->getEntity(this->mineralPosition);
    if (!entity)
        return;

    Mineral* mineral = dynamic_cast<Mineral*>(entity);
    if (!mineral)
        return;

    player->mine(*mineral);
}
