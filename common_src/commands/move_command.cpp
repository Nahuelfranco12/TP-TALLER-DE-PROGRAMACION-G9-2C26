#include "move_command.h"

void MoveCommand::execute(World& world) {
    Player* player = world.getPlayer(this->playerId);
    if (!player)
        return;

    Position destination(player->position.x, player->position.y);
    switch (this->direction) {
        case Direction::Up:
            destination.y = player->position.y + 1;
            break;
        case Direction::Down:
            destination.y = player->position.y - 1;
            break;
        case Direction::Left:
            destination.x = player->position.x + 1;
            break;
        case Direction::Right:
            destination.x = player->position.x - 1;
            break;
    }
    player->move(destination);
}
