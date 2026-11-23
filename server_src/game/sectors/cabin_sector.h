#ifndef CABIN_SECTOR_H_
#define CABIN_SECTOR_H_

#include "sector.h"
#include "../game_constants.h"
#include "../entities/bed.h"
#include "../position.h"

class CabinSector : public Sector {
private:
    int ownerPlayerId;

    // TODO: logica para agregar cofres (puede ser un map de <Position, Chest>)
    // TODO: logica para mas productos de decoracion.

public:
    CabinSector(int ownerPlayerId, IdSector id)
        : Sector(CABIN_DIMENSION_1, CABIN_DIMENSION_2, id,
                 Terrain(true, false, TerrainType::WOOD)),
          ownerPlayerId(ownerPlayerId) {}
    
};

#endif // CABIN_SECTOR_H_
