#ifndef COMMUNITY_CENTER_SECTOR_H_
#define COMMUNITY_CENTER_SECTOR_H_

#include "sector.h"

class CommunityCenterSector : public Sector {
private:
public:
  CommunityCenterSector(size_t width, size_t height)
      : Sector(width, height, IdSector::COMMUNITY_CENTER,
               Terrain(true, false, TerrainType::GRASS)) {}
};

#endif // COMMUNITY_CENTER_SECTOR_H_