#ifndef VILLAGE_SECTOR_H_
#define VILLAGE_SECTOR_H_

#include "sector.h"

class VillageSector : public Sector {
private:
public:
    VillageSector(size_t width, size_t height) : Sector(width, height, IdSector::VILLAGE, Terrain(true, false, TerrainType::GRASS)) {}
};

#endif // VILLAGE_SECTOR_H_
