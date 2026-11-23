#ifndef VILLAGE_SECTOR_H_
#define VILLAGE_SECTOR_H_

#include "sector.h"

class VillageSector : public Sector {
private:
public:
  VillageSector(size_t width, size_t height,
                std::map<Position, TerrainDecoration> decorations = {},
                std::vector<Building> buildings = {})
      : Sector(width, height, IdSector::VILLAGE,
               Terrain(true, false, TerrainType::GRASS), std::move(decorations),
               std::move(buildings)) {}
};

#endif // VILLAGE_SECTOR_H_
