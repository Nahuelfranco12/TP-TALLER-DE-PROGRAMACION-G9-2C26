#include "cheat_end_day_command.h"

#include "../../world.h"

void CheatEndDayCommand::execute(World &world) { world.endDayCheat(); }