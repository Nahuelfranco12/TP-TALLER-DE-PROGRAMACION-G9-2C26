#include "door.h"

#include <memory>
#include <utility>

#include "../sectors/sector.h"

bool Door::moveEntity(std::unique_ptr<Entity>& entity,
                       Position& destinePosition) {
  if (this->destineSector.canMoveTo(this->destinePosition) &&
      this->destineSector.tryAddEntity(entity, this->destinePosition)) {
    destinePosition = this->destinePosition;
    return true;
  }

  Position freePosition(0, 0);
  if (!this->destineSector.findFreePosition(freePosition))
    return false;

  if (!this->destineSector.tryAddEntity(entity, freePosition))
    return false;

  destinePosition = freePosition;
  return true;
}


EntityState Door::entityState() const {
  EntityState state = Entity::entityState();
  state.door.type = type;
  return state;
}
