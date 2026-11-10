#include "till_command.h"

#include "../world.h"

void TillCommand::execute(World &world) {
    Player *player = world.getPlayer(this->playerId);
    if (!player)
        return;

    Tool *tool = player->getSelectedTool();
    if (!tool || tool->toolType != AvailableTools::SHOVEL)
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

    sector->till(targetPos);
}