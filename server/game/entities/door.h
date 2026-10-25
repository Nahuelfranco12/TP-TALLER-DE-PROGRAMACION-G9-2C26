#ifndef DOOR_H_
#define DOOR_H_

#include "../id_sector.h"
#include "../position.h"
#include "entity.h"

class Door : public Entity {
private:
    IdSector idDestineSector;
    Position destinePosition;
};

#endif // DOOR_H_