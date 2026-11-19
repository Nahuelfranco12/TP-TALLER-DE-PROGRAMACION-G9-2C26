#include "cheat_enemies_damage_command.h"

#include "../../world.h"

void CheatEnemiesDamageCommand::execute(World &world) { world.cavernCheat(); }