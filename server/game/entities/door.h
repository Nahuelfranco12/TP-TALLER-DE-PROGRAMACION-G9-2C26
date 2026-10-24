#ifndef DOOR_H_
#define DOOR_H_

#include "../id_sector.h"
#include "../position.h"

class Door {
private:
    IdSector idDestineSector;
    Position destinePosition;
};

#endif // DOOR_H_