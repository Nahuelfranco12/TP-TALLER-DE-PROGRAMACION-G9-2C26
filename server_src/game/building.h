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

  Building()
      : type(),
        topLeft({0, 0}),
        width(0),
        height(0),
        door({0, 0}),
        interior(),
        ownerId(-1) {}

  Building(BuildingType type, Position topLeft, size_t width, size_t height, Position door, IdSector interior, int ownerId) : type(type), topLeft(topLeft), width(width), height(height), door(door), interior(interior), ownerId(ownerId) {}
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
