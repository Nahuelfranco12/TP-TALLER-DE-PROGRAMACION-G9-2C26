#ifndef SECTOR_H_
#define SECTOR_H_

#include <cstddef>
#include <map>
#include <vector>

#include "position.h"
#include "terrain.h"
#include "./entities/entity.h"
#include "./entities/door.h"
#include "id_sector.h"
#include "move_result.h"
#include "terrain.h"

class Sector {
private:
    size_t width;
    size_t height;
    IdSector id;
    std::vector<std::vector<Terrain>> tiles;
    std::map<Position, Entity> entities;
    std::map<Position, Door> doors;

public:
    Sector(size_t width, size_t height, IdSector id) : width(width), height(height), tiles(width, std::vector<Terrain>(height, Terrain(true, false, TerrainType::GRASS))), id(id) {};

    MoveResult move(Entity& entity, Position origin, Position destine);
    bool isEmpty(Position pos);
    bool addEntity(Entity& entity, Position pos);
    void removeEntity(Position pos);
};

#endif // SECTOR_H_