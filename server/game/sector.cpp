#include "sector.h"

MoveResult Sector::move(Entity& entity, Position origin, Position destine) {
    auto [it, inserted] = this->entities.try_emplace(destine, entity);
    if (inserted) {
        this->entities.erase(origin);
        return MoveResult(inserted, destine, this->id);
    }
    return MoveResult(inserted, origin, this->id);

    // TODO: revisar el caso en que haya puerta
}

bool Sector::isEmpty(Position pos) {
    if (this->entities.count(pos) || this->doors.count(pos))
        return false;
    return true;
}

bool Sector::addEntity(Entity& entity, Position pos) {
    auto [it, inserted] = this->entities.try_emplace(pos, entity);
    return inserted;
}

void Sector::removeEntity(Position pos) {
    this->entities.erase(pos);
}
