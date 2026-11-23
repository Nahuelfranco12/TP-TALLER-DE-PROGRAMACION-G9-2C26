#include "cheat_water_crop_command.h"

#include "../../entities/crop.h"
#include "../../world.h"

void CheatWaterCropCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;

  Position target(player->position.x, player->position.y);
  switch (this->direction) {
  case DirectionDto::Up:
    target.y -= 1;
    break;
  case DirectionDto::Down:
    target.y += 1;
    break;
  case DirectionDto::Left:
    target.x -= 1;
    break;
  case DirectionDto::Right:
    target.x += 1;
    break;
  }

  Sector *sector = player->getActualSector();
  if (!sector)
    return;

  Crop *crop = dynamic_cast<Crop *>(sector->getEntity(target));
  if (!crop)
    return;

  crop->forceWater();
}