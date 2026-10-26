#ifndef DOOR_H_
#define DOOR_H_

#include "../id_sector.h"
#include "../position.h"
#include "entity.h"

class Door : public Entity {
private:
    IdSector idDestineSector;
    Position destinePosition;

public:
    Door(size_t pos_x, size_t pos_y, IdSector idDestineSector, Position destinePosition) : Entity(pos_x, pos_y), idDestineSector(idDestineSector), destinePosition(destinePosition) {};
};

#endif // DOOR_H_