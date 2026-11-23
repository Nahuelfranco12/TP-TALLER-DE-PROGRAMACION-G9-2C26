#ifndef BUILDING_H_
#define BUILDING_H_

#include "game_constants.h"
#include "position.h"

struct Building {
  BuildingType type;
  Position topLeft;
  size_t width;
  size_t height;
  Position door;
  IdSector interior;
  int ownerId;
};

inline IdSector cabinSectorId(int playerId) {
  return static_cast<IdSector>(
      static_cast<int>(IdSector::CABIN_PLAYER_1) + playerId);
}

inline BuildingType cabinBuildingType(int playerId) {
  return static_cast<BuildingType>(
      static_cast<int>(BuildingType::CABIN_PLAYER_1) + playerId);
}

#endif // BUILDING_H_