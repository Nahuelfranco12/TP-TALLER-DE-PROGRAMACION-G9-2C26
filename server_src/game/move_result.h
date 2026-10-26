#ifndef MOVE_RESULT_H_
#define MOVE_RESULT_H_

#include "position.h"
#include "id_sector.h"

class MoveResult {
public:
    bool success;
    Position position;
    IdSector idSector;

    MoveResult(bool success, Position position, IdSector idSector) :  success(success), position(position), idSector(idSector) {};
};

#endif // MOVE_RESULT_H_
