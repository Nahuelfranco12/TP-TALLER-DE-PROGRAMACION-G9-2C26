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

  bool placeCabin(Position top, Position &doorPos) {
    for (size_t dx = 0; dx < CABIN_OUTSIDE_WIDTH; dx++)
      for (size_t dy = 0; dy < CABIN_OUTSIDE_HEIGHT; dy++)
        if (!canMoveTo({top.x + dx, top.y + dy}))
          return false;

    doorPos = {top.x + CABIN_OUTSIDE_WIDTH / 2, top.y + CABIN_OUTSIDE_HEIGHT - 1};

    for (size_t dx = 0; dx < CABIN_OUTSIDE_WIDTH; dx++)
      for (size_t dy = 0; dy < CABIN_OUTSIDE_HEIGHT; dy++) {
        Position p{top.x + dx, top.y + dy};
        if (p != doorPos)
          blockTile(p, TerrainType::HOUSE);
      }
    return true;
  }
};

#endif // FARM_SECTOR_H_
