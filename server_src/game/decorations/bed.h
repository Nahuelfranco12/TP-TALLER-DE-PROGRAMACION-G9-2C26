#ifndef BED_H_
#define BED_H_

#include "../position.h"
#include "../game_constants.h"

class Bed {
private:
    int ownerPlayerId;
    IdSector sector;
    Position position;
    bool inBed;

public:
    Bed(int ownerPlayerId, IdSector sector, Position position) : ownerPlayerId(ownerPlayerId), sector(sector), position(position), inBed(false) {}

    void interact() {
        inBed = !inBed;
    };

    bool isPlayerInBed() { return this->inBed; }
};

#endif // BED_H_
