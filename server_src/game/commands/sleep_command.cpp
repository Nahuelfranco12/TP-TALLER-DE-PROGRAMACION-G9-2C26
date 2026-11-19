#include "sleep_command.h"

#include "../world.h"
#include "../sectors/cabin_sector.h"

void SleepCommand::execute(World &world) {
  Player *player = world.getPlayer(playerId);
  if (!player)
    return;

  CabinSector *cabin = dynamic_cast<CabinSector *>(player->getActualSector());
  if (!cabin)
    return;

  cabin->trySleep(playerId, player->position);
}
