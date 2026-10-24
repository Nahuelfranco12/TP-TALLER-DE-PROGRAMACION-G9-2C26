#ifndef SECTOR_H_
#define SECTOR_H_

#include <cstddef>
#include <map>

#include "position.h"
#include "terrain.h"
#include "./entities/entity.h"
#include "./entities/door.h"
#include "id_sector.h"

class Sector {
private:
    size_t width;
    size_t height;
    IdSector id;
    Terrain tiles[width][height];
    std::map<Position, Entity> entities;
    std::map<Position, Door> doors;

public:    
};

#endif // SECTOR_H_