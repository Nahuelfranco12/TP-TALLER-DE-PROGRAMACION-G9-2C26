#include "sector.h"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "../cheatable/growth_cheat.h"
#include "../entities/enemies/enemy.h"
#include "../entities/enemies/trap.h"
#include "../entities/player.h"

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
    Position destinePos(0, 0);
    if (!door.moveEntity(entity, destinePos)) {
      entity->setPosition(origin);
      this->entities.emplace(origin, std::move(entity));
      return MoveResult(false, origin, this->id);
    }
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

bool Sector::placeBuilding(const Building &building) {
  for (size_t dx = 0; dx < building.width; dx++)
    for (size_t dy = 0; dy < building.height; dy++)
      if (!canMoveTo({building.topLeft.x + dx, building.topLeft.y + dy}))
        return false;

  for (size_t dx = 0; dx < building.width; dx++)
    for (size_t dy = 0; dy < building.height; dy++) {
      Position p{building.topLeft.x + dx, building.topLeft.y + dy};
      if (p == building.door) continue;
        blockTile(p, TerrainType::HOUSE);
    }

  buildings.push_back(building);
  return true;
}

bool Sector::tryAddEntity(std::unique_ptr<Entity> &entity, Position pos) {
  if (auto *trap = dynamic_cast<Trap *>(entity.get())) {
    if (this->traps.find(pos) != this->traps.end())
      return false;

    trap->setPosition(pos);
    std::unique_ptr<Trap> trapEntity(
        static_cast<Trap *>(entity.release()));
    auto [it, inserted] = this->traps.try_emplace(pos, std::move(trapEntity));
    return inserted;
  }

  if (!isEmpty(pos))
    return false;

  entity->setPosition(pos);
  auto [it, inserted] = this->entities.try_emplace(pos, std::move(entity));
  return inserted;
}

bool Sector::addDoor(std::unique_ptr<Door> door, Position pos) {
  // TODO: revisar este caso, el cual es cuando en la posicion ya hay una
  // entidad.
  if (!canMoveTo(pos))
    return false;
  auto [it, inserted] = this->doors.try_emplace(pos, std::move(door));
  return inserted;
}

void Sector::growthCheatAll() {
  for (auto &[pos, entity] : this->entities) {
    if (auto *cheatable = dynamic_cast<IGrowthCheat *>(entity.get()))
      cheatable->growthCheat();
  }
}

void Sector::cheatEnemies() {
  for (auto &[position, entityPtr] : this->entities) {
    if (entityPtr->getType() == EntityTypes::ENEMY) {
      static_cast<Enemy &>(*entityPtr).cheat();
    }
  }
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

size_t Sector::playerCount() const {
  size_t count = 0;
  for (const auto &[pos, entity] : entities)
    if (entity->getType() == EntityTypes::PLAYER)
      count++;
  return count;
}

bool Sector::findFreePosition(Position &freePosition) const {
  for (size_t x = 0; x < this->width; x++)
    for (size_t y = 0; y < this->height; y++) {
      Position pos(x, y);
      if (this->tiles[x][y].isTransitable() &&
          this->entities.find(pos) == this->entities.end() &&
          this->traps.find(pos) == this->traps.end()) {
        freePosition = pos;
        return true;
      }
    }
  return false;
}

Position Sector::findFreePosition() const {
  Position freePosition(0, 0);
  if (findFreePosition(freePosition))
    return freePosition;
  return Position(0, 0);
}

bool Sector::till(Position pos) {
  if (pos.x >= this->width || pos.y >= this->height)
    return false;
  if (!isEmpty(pos))
    return false;
  return this->tiles[pos.x][pos.y].till();
}
bool Sector::isTilled(Position pos) const {
  if (pos.x >= this->width || pos.y >= this->height)
    return false;
  return this->tiles[pos.x][pos.y].isTilled();
}

SectorState Sector::state() const {
  SectorState state{id, width, height, {}, {}};

  state.entities.reserve(entities.size() + traps.size());
  for (const auto &[pos, entity] : entities)
    state.entities.push_back(entity->entityState());
  for (const auto &[pos, trap] : traps)
    state.entities.push_back(trap->entityState());

  state.tiles.assign(width, std::vector<TerrainState>(height));
  for (size_t x = 0; x < width; ++x)
    for (size_t y = 0; y < height; ++y) {
      const Terrain &terrain = tiles[x][y];
      state.tiles[x][y] = {
          terrain.getTerrainType(), terrain.getTerrainDecoration(), terrain.isTransitable(), terrain.isArable(),
          this->doors.find(Position(x, y)) != this->doors.end(),
          terrain.isTilled()};
    }

  state.buildings.reserve(buildings.size());
  for (const auto &b : buildings)
    state.buildings.push_back({b.type, b.topLeft, b.width, b.height,
                              b.door, b.interior, b.ownerId});

  return state;
}

bool Sector::closestPlayer(Position origin, int maxDistance,
                           Position &closestPosition) const {
  bool foundAny = false;
  int closestDistance = maxDistance + 1;

  for (const auto &[playerPosition, entity] : entities) {
    const Player *player = dynamic_cast<const Player *>(entity.get());
    if (!player || player->isUnconscious())
      continue;

    int distance = std::abs(static_cast<int>(playerPosition.x) -
                            static_cast<int>(origin.x)) +
                   std::abs(static_cast<int>(playerPosition.y) -
                            static_cast<int>(origin.y));

    if (distance < closestDistance) {
      closestDistance = distance;
      closestPosition = playerPosition;
      foundAny = true;
    }
  }
  return foundAny;
}

void Sector::apply(Position origin, const Decision &decision) {
  Enemy *enemy = dynamic_cast<Enemy *>(getEntity(origin));
  if (!enemy || enemy->isDead())
    return;
  enemy->apply(*this, origin, decision);
}

void Sector::tick() {
  for (auto &[pos, entity] : this->entities) {
    entity->tick();
  }

  for (auto &[pos, trap] : this->traps)
    trap->tick();

  for (const auto &[pos, trap] : this->traps) {
    if (!trap->wasTriggered())
      continue;
    trap->activate(*this);
  }

  std::map<Position, Decision> decisions;
  for (auto &[pos, entity] : this->entities) {
    Enemy *enemy = dynamic_cast<Enemy *>(entity.get());
    if (enemy)
      decisions[pos] = enemy->decide(*this);
  }

  for (const auto &[pos, decision] : decisions)
    apply(pos, decision);
}
