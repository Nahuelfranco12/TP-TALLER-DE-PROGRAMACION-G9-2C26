#ifndef CABIN_SECTOR_H_
#define CABIN_SECTOR_H_

#include "sector.h"
#include "../game_constants.h"
#include "../entities/bed.h"
#include "../position.h"

class CabinSector : public Sector {
private:
    int ownerPlayerId;

    std::pair<Position, std::unique_ptr<Bed>> bed;

    // TODO: logica para agregar cofres (puede ser un map de <Position, Chest>)
    // TODO: logica para mas productos de decoracion.

public:
    CabinSector(int ownerPlayerId, IdSector id, Position bedPos)
        : Sector(CABIN_DIMENSION_1, CABIN_DIMENSION_2, id,
                 Terrain(true, false, TerrainType::WOOD)),
          ownerPlayerId(ownerPlayerId),
          bed(bedPos, std::make_unique<Bed>(bedPos)) {}

    bool trySleep(int playerId, Position position) {
        if (playerId != ownerPlayerId || !bed.first.isAdjacentTo(position))
            return false;
        return bed.second->sleep();
    }

    bool isPlayerSleeping() const {
        return bed.second->isSleeping();
    }

    Position getBedPosition() const { return bed.first; }

    bool findBedSpawnPosition(Position &spawnPosition) const {
        Position candidates[] = {
            Position(bed.first.x + 1, bed.first.y),
            Position(bed.first.x, bed.first.y + 1),
            Position(bed.first.x > 0 ? bed.first.x - 1 : 0, bed.first.y),
            Position(bed.first.x, bed.first.y > 0 ? bed.first.y - 1 : 0)};

        for (const Position &candidate : candidates)
            if (canMoveTo(candidate)) {
            spawnPosition = candidate;
            return true;
        }
        return findFreePosition(spawnPosition);
    }

    void endDay() override {
        bed.second->setSleeping(false);
    }

    SectorState state() const override {
        SectorState result = Sector::state();
        result.entities.push_back(bed.second->entityState());
        return result;
    }    
};

#endif // CABIN_SECTOR_H_
