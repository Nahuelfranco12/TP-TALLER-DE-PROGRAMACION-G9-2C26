#include "trap.h"

#include "../../sectors/sector.h"
#include "../player.h"

void Trap::activate(Sector &sector) const {
  Position target = position;

  if (trapType == EnemyType::TRAP_FLAME) {
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);

    switch (direction) {
    case DirectionDto::Up:
      y--;
      break;
    case DirectionDto::Down:
      y++;
      break;
    case DirectionDto::Left:
      x--;
      break;
    case DirectionDto::Right:
      x++;
      break;
    }

    if (x < 0 || y < 0 || x >= static_cast<int>(sector.getWidth()) ||
        y >= static_cast<int>(sector.getHeight()))
      return;

    target = Position(static_cast<size_t>(x), static_cast<size_t>(y));
  }

  Player *player = dynamic_cast<Player *>(sector.getEntity(target));
  if (player && !player->isUnconscious())
    player->takeDamage(damage);
}