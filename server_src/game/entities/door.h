#ifndef DOOR_H_
#define DOOR_H_

#include <memory>

#include "../game_constants.h"
#include "../position.h"
#include "entity.h"

class Sector;

class Door {
private:
  DoorType type;
  Position position;
  IdSector idDestineSector;
  Sector &destineSector;
  Position destinePosition;

public:
  Door(DoorType type, Position position, IdSector idDestineSector, Sector &destineSector,
       Position destinePosition)
      : type(type), position(position), idDestineSector(idDestineSector),
        destineSector(destineSector), destinePosition(destinePosition) {}

  DoorType getDoorType() const { return type; }
  IdSector getIdDestineSector() const { return idDestineSector; }
  Sector &getDestineSector() const { return destineSector; }
  Position getDestinePosition() const { return destinePosition; }

  /*
   * Move the entity standing on the door to the target sector.
   * Returns:
   *  - Door destine position when the destine position is empty.
   *  - Any free position finded where the entity now is placed.
   */
  bool moveEntity(std::unique_ptr<Entity>& entity, Position& destinePosition);
};

#endif // DOOR_H_
