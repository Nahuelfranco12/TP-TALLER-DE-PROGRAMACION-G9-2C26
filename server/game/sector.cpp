#include "sector.h"

MoveResult Sector::move(Position origin, Position destine) {
    if (!this->isEmpty(destine)) {
        auto it = this->entities.find(origin);
        IdSector current = this->id;
        if (it == this->entities.end())
            return MoveResult(false, origin, current);
        return MoveResult(false, it->second->position, current);
    }

    auto it = this->entities.find(origin);
    if (it == this->entities.end())
        return MoveResult(false, origin, this->id);

    std::unique_ptr<Entity> entity = std::move(it->second);
    this->entities.erase(it);

    entity->setPosition(destine);
    this->entities.emplace(destine, std::move(entity));

    return MoveResult(true, destine, this->id);

    // TODO: revisar el caso en que haya puerta
}

bool Sector::isEmpty(Position pos) {
    if (this->entities.count(pos) || this->doors.count(pos))
        return false;
    return true;
}

bool Sector::addEntity(std::unique_ptr<Entity> entity, Position pos) {
    auto [it, inserted] = this->entities.try_emplace(pos, std::move(entity));
    return inserted;
}

std::unique_ptr<Entity> Sector::removeEntity(Position pos) {
    auto it = this->entities.find(pos);
    if (it == this->entities.end())
        return nullptr;
    std::unique_ptr<Entity> entity = std::move(it->second);
    this->entities.erase(it);
    return entity;
}

Entity* Sector::getEntity(Position pos) {
    auto it = this->entities.find(pos);
    if (it == this->entities.end())
        return nullptr;
    return it->second.get();
}
