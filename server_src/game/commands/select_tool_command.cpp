#include "select_tool_command.h"

void SelectToolCommand::execute(World &world) {
    Player* player = world.getPlayer(this->playerId);
    if (player != nullptr)
        player.selectTool(this->tool);
}
