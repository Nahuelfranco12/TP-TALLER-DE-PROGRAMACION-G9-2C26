#ifndef SECTOR_H_
#define SECTOR_H_

#include <cstddef>
#include <map>
#include <memory>
#include <vector>

#include "game_constants.h"
#include "move_result.h"
#include "position.h"
#include "terrain.h"
#include "entities/door.h"
#include "entities/entity.h"

class Sector {
private:
    size_t width;
    size_t height;
    IdSector id;
    std::vector<std::vector<Terrain>> tiles;
    std::map<Position, std::unique_ptr<Entity>> entities;
    std::map<Position, Door> doors;

public:
    Sector(size_t width, size_t height, IdSector id) : width(width), height(height), id(id), tiles(width, std::vector<Terrain>(height, Terrain(true, false, TerrainType::GRASS))) {}

    virtual ~Sector() = default;

    MoveResult move(Position origin, Position destine);
    
    bool canMoveTo(Position pos) const;
    bool isEmpty(Position pos) const;

    bool addEntity(std::unique_ptr<Entity> entity, Position pos);
    std::unique_ptr<Entity> removeEntity(Position pos);

    bool addDoor(std::unique_ptr<Door> door, Position pos);
    // std::unique_ptr<Door> removeDoor(Position pos);

    Entity* getEntity(Position pos) const;
    Position findFreePosition() const;

    IdSector getId() const { return id;     }
    size_t getWidth() const { return width;  }
    size_t getHeight() const { return height; }
};

#endif // SECTOR_H_
