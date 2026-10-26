#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <memory>

#include "id_player.h"
#include "id_sector.h"
#include "mineral_types.h"
#include "position.h"
#include "sector.h"
#include "entities/animal.h"
#include "entities/player.h"

enum DaySpeed { SLOW, MEDIUM, FAST };

class World {
private:
    DaySpeed speed;
    std::map<IdSector, Sector> sectors;
    std::map<IdPlayer, Player*> players;
    IdPlayer nextPlayerId = 0;

public:
    explicit World(DaySpeed speed) : speed(speed) {}

    bool addSector(IdSector id, size_t width = 30, size_t height = 30);
    
    IdPlayer addPlayer(IdSector idSector);
    
    bool spawnMineral(IdSector sectorId, Position pos, MineralTypes type, double freq, MineralPickaxeTime pickaxeTime);
    bool spawnAnimal(IdSector sectorId, Position pos, AnimalType type);

    // TODO: implementar con puertas
    bool transfer(Entity& e, IdSector destine, Position pos);

    Player* getPlayer(IdPlayer id);
    Sector* getSector(IdSector id);
};

#endif // WORLD_H_