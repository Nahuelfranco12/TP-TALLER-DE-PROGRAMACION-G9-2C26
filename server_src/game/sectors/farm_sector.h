#ifndef FARM_SECTOR_H_
#define FARM_SECTOR_H_

#include "sector.h"

#include <optional>

class FarmSector : public Sector {
private:
public:
  FarmSector(size_t width, size_t height,
             std::map<Position, TerrainDecoration> decorations = {},
             std::vector<Building> buildings = {})
      : Sector(width, height, IdSector::FARM,
               Terrain(true, true, TerrainType::GRASS), std::move(decorations),
               std::move(buildings)) {}

  bool placeAnimal(Position position, AnimalType animalType);

  std::optional<Building> placeCabin(int playerId, Position top) {
    Building b{
        .type = cabinBuildingType(playerId),
        .topLeft = top,
        .width = CABIN_OUTSIDE_WIDTH,
        .height = CABIN_OUTSIDE_HEIGHT,
        .door = Position(top.x + CABIN_OUTSIDE_WIDTH / 2,
                        top.y + CABIN_OUTSIDE_HEIGHT - 1),
        .interior = cabinSectorId(playerId),
        .ownerId = playerId};

    if (!placeBuilding(b))
      return std::nullopt;
    return b;
  }
};

#endif // FARM_SECTOR_H_
