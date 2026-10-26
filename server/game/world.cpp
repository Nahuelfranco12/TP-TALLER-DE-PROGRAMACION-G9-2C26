#include "world.h"

bool World::addSector(IdSector id) {
    Sector sector(30, 30, id);
    auto [it, inserted] = this->sectors.try_emplace(id, sector);
    return inserted;
}

IdPlayer World::addPlayer(IdSector idSector) {
    auto sectorIt = this->sectors.find(idSector);
    if (sectorIt == this->sectors.end()) return INVALID_PLAYER_ID;

    Sector& sector = sectorIt->second;
    Position startPos = sector.findFreePosition();

    auto player = std::make_unique<Player>(startPos.x, startPos.y, &sector);
    Player* playerPtr = player.get();

    if (!sector.addEntity(std::move(player), startPos))
        return INVALID_PLAYER_ID;

    IdPlayer id = this->nextPlayerId++;
    this->players.emplace(id, playerPtr);
    return id;
}
}

bool transfer(Entity& e, IdSector destine, Position pos) {
    // TODO: implementar
    return false; 
}