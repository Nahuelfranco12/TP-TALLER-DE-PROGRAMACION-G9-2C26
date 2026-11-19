#ifndef SECTOR_H_
#define SECTOR_H_

#include <cstddef>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "../../world_state.h"
#include "../decision.h"
#include "../entities/door.h"
#include "../entities/entity.h"
#include "../entities/enemies/trap.h"
#include "../entities/player.h"
#include "../game_constants.h"
#include "../move_result.h"
#include "../position.h"
#include "../terrain.h"
#include "../building.h"

class Sector {
protected:
  size_t width;
  size_t height;
  IdSector id;
  std::vector<std::vector<Terrain>> tiles;
  std::vector<Building> buildings;
  std::map<Position, std::unique_ptr<Entity>> entities;
  std::map<Position, std::unique_ptr<Trap>> traps;
  std::map<Position, std::unique_ptr<Door>> doors;

public:
  Sector(size_t width, size_t height, IdSector id, const Terrain &baseTerrain,
         std::map<Position, TerrainDecoration> decorations = {},
         std::vector<Building> buildings = {})
      : width(width), height(height), id(id),
        tiles(width, std::vector<Terrain>(height, baseTerrain)) {
    for (const auto &[position, decoration] : decorations) {
      if (position.x < width && position.y < height) {
        Terrain &terrain = tiles[position.x][position.y];
        terrain = Terrain(terrain.isTransitable(), terrain.isArable(),
                          terrain.getTerrainType(), decoration);
      }
    for (const Building &building : buildings)
      placeBuilding(building);
    }
  }
  virtual ~Sector() = default;

  MoveResult move(Position origin, Position destine);
  bool canMoveTo(Position pos) const;
  bool isEmpty(Position pos) const;
  Position findFreePosition() const;
  bool findFreePosition(Position &freePosition) const;
  void blockTile(Position pos, TerrainType type) {
    if (pos.x >= width || pos.y >= height)
      return;
    tiles[pos.x][pos.y] = Terrain(false, false, type, TerrainDecoration::NONE);
  }
    
  bool placeBuilding(const Building &building);

  virtual bool tryAddEntity(std::unique_ptr<Entity> &entity, Position pos);
  std::unique_ptr<Entity> removeEntity(Position pos);
  bool addDoor(std::unique_ptr<Door> door, Position pos);
  // std::unique_ptr<Door> removeDoor(Position pos);

  void growthCheatAll();
  void cheatEnemies();

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
  virtual void reset(){};
  virtual void endDay(){};

  bool till(Position pos);
  bool isTilled(Position pos) const;

  bool closestPlayer(Position origin, int maxDistance,
                     Position &closestPosition) const;
  void apply(Position origin, const Decision &decision);

  bool bloodNear(Position origin, int radius) const {
    for (const auto &[playerPosition, entity] : entities) {
      const Player *player = dynamic_cast<const Player *>(entity.get());
      if (!player || !player->isBadlyHurt()) {
        continue;
      }
      int distance = std::abs(static_cast<int>(playerPosition.x) -
                              static_cast<int>(origin.x)) +
                     std::abs(static_cast<int>(playerPosition.y) -
                              static_cast<int>(origin.y));
      if (distance <= radius)
        return true;
    }
    return false;
  }

  /*
   * State para obtener el estado del sector completo y poder serializarlo.
   */
  virtual SectorState state() const;
};

#endif // SECTOR_H_
