#include "move_command.h"
#include "../world.h"

void MoveCommand::execute(World& world) {
    Player* player = world.getPlayer(this->playerId);
    if (!player)
        return;
    player->move(this->destination);
}
