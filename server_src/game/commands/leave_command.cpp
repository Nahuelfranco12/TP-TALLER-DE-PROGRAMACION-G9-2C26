#include "leave_command.h"

void LeaveCommand::execute(World &world) { world.removePlayer(this->playerId); }
