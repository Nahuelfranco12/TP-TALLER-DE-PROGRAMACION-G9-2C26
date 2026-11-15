#ifndef SECTOR_H_
#define SECTOR_H_

#include <cstddef>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "../../world_state.h"
#include "../entities/door.h"
#include "../entities/entity.h"
#include "../game_constants.h"
#include "../move_result.h"
#include "../position.h"
#include "../terrain.h"

struct PendingRespawn {
  Position pos;
  int ticksLeft;
};

class Sector {
protected:
  size_t width;
  size_t height;
  IdSector id;
  std::vector<std::vector<Terrain>> tiles;
  std::map<Position, std::unique_ptr<Entity>> entities;
  std::map<Position, std::unique_ptr<Door>> doors;

public:
  Sector(size_t width, size_t height, IdSector id, Terrain terrainType)
      : width(width), height(height), id(id),
        tiles(width, std::vector<Terrain>(height, terrainType)) {}
  virtual ~Sector() = default;

  MoveResult move(Position origin, Position destine);
  bool canMoveTo(Position pos) const;
  bool isEmpty(Position pos) const;
  Position findFreePosition() const;

  virtual bool addEntity(std::unique_ptr<Entity> entity, Position pos);
  std::unique_ptr<Entity> removeEntity(Position pos);
  bool addDoor(std::unique_ptr<Door> door, Position pos);
  // std::unique_ptr<Door> removeDoor(Position pos);

  void growthCheatAll();

  /*
   * getters
   */

  Entity *getEntity(Position pos) const;
  IdSector getId() const { return id; }
  size_t getWidth() const { return width; }
  size_t getHeight() const { return height; }
  const Terrain &getTerrain(Position pos) const { return tiles[pos.x][pos.y]; }
  size_t playerCount() const;

  void tick();
  virtual void reset() {};
  virtual void endDay() {};

  bool till(Position pos);
  bool isTilled(Position pos) const;

  /*
   * State para obtener el estado del sector completo y poder serializarlo.
   */
  SectorState state() const;
};

#endif // SECTOR_H_
