#include "door.h"

#include <utility>

Position Door::moveEntity(std::unique_ptr<Entity> entity) {
    if (this->destineSector.canMoveTo(this->destinePosition)) {
        this->destineSector.addEntity(std::move(entity), this->destinePosition);
        return this->destinePosition;
    }
    Position freePos = this->destineSector.findFreePosition();
    this->destineSector.addEntity(std::move(entity), freePos);
    return freePos;
}
