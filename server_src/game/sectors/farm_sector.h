#ifndef FARM_SECTOR_H_
#define FARM_SECTOR_H_

#include "sector.h"

class FarmSector : public Sector {
private:
public:
  FarmSector(size_t width, size_t height)
      : Sector(width, height, IdSector::FARM,
               Terrain(true, true, TerrainType::GRASS)) {}

  bool placeAnimal(Position position, AnimalType animalType);
};

#endif // FARM_SECTOR_H_
