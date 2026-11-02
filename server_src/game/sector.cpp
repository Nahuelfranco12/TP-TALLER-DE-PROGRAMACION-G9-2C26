#include "sector.h"

#include <utility>

MoveResult Sector::move(Position origin, Position destine) {
  if (!canMoveTo(destine)) {
    auto it = this->entities.find(origin);
    Position current =
        (it != this->entities.end()) ? it->second->position : origin;
    return MoveResult(false, current, this->id);
  }
  auto it = this->entities.find(origin);
  if (it == this->entities.end())
    return MoveResult(false, origin, this->id);
  std::unique_ptr<Entity> entity = std::move(it->second);
  this->entities.erase(it);

  if (this->doors.find(destine) == this->doors.end()) {
    // Si no hay puerta mueve directo
    entity->setPosition(destine);
    this->entities.emplace(destine, std::move(entity));
    return MoveResult(true, destine, this->id);
  } else {
    // Si hay puerta se le pide a la puerta que mueva la entidad
    Door &door = *this->doors.at(destine);
    Position destinePos = door.moveEntity(std::move(entity));
    return MoveResult(true, destinePos, door.getIdDestineSector());
  }
}

bool Sector::canMoveTo(Position pos) const {
  if (pos.x >= this->width || pos.y >= this->height)
    return false;
  if (!this->tiles[pos.x][pos.y].isTransitable())
    return false;
  return isEmpty(pos);
}

bool Sector::isEmpty(Position pos) const {
  return this->entities.find(pos) == this->entities.end();
}

bool Sector::addEntity(std::unique_ptr<Entity> entity, Position pos) {
  if (!isEmpty(pos))
    return false;

  entity->setPosition(pos);
  auto [it, inserted] = this->entities.try_emplace(pos, std::move(entity));
  return inserted;
}

bool Sector::addDoor(std::unique_ptr<Door> door, Position pos) {
  auto [it, inserted] = this->doors.try_emplace(pos, std::move(door));
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

Entity *Sector::getEntity(Position pos) const {
  auto it = this->entities.find(pos);
  if (it == this->entities.end())
    return nullptr;
  return it->second.get();
}

Position Sector::findFreePosition() const {
  for (size_t x = 0; x < this->width; x++)
    for (size_t y = 0; y < this->height; y++) {
      Position pos(x, y);
      if (this->entities.find(pos) == this->entities.end())
        return pos;
    }
  return Position(0, 0);
}

SectorState Sector::state() const {
  SectorState state{id, width, height, {}, {}};

  state.entities.reserve(entities.size());
  for (const auto &[pos, entity] : entities)
    state.entities.push_back(entity->entityState());

  state.tiles.assign(width, std::vector<TerrainState>(height));
  for (size_t x = 0; x < width; ++x)
    for (size_t y = 0; y < height; ++y) {
      const Terrain &terrain = tiles[x][y];
      state.tiles[x][y] = {terrain.getTerrainType(),
                                 terrain.isTransitable(), terrain.isArable()};
    }

  return state;
}
