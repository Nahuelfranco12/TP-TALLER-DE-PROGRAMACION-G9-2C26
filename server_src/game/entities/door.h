#ifndef DOOR_H_
#define DOOR_H_

#include <memory>

#include "../game_constants.h"
#include "../position.h"
#include "entity.h"

class Sector;

class Door {
private:
    Position position;
    IdSector idDestineSector;
    Sector& destineSector;
    Position destinePosition;

public:
    Door(size_t pos_x, size_t pos_y, IdSector idDestineSector, Sector& destineSector, Position destinePosition) : position(pos_x, pos_y), idDestineSector(idDestineSector), destineSector(destineSector), destinePosition(destinePosition) {};

    IdSector getIdDestineSector() const { return idDestineSector; }
    Sector& getDestineSector() const { return destineSector; }
    Position getDestinePosition() const { return destinePosition; }

    /*
    * Move the entity standing on the door to the target sector.   
    * Returns:
    *  - Door destine position when the destine position is empty.
    *  - Any free position finded where the entity now is placed. 
    */
    Position moveEntity(std::unique_ptr<Entity> entity);
};

#endif // DOOR_H_