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
    Building b(cabinBuildingType(playerId), top, CABIN_OUTSIDE_WIDTH, CABIN_OUTSIDE_HEIGHT, Position(top.x + CABIN_OUTSIDE_WIDTH / 2, top.y + CABIN_OUTSIDE_HEIGHT - 1), cabinSectorId(playerId), playerId);

    if (!placeBuilding(b))
      return std::nullopt;
    return b;
  }

  bool hasRoomFor(AnimalType type) const;
};

#endif // FARM_SECTOR_H_
