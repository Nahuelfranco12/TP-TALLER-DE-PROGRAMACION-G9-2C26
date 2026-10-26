#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <list>

#include "id_sector.h"
#include "sector.h"
#include "./entities/player.h"

enum DaySpeed { SLOW, MEDIUM, FAST };

class World {
private:
    DaySpeed speed;

    std::map<IdSector, Sector> sectors;
    std::list<Player> players;

public:
    World(DaySpeed speed) : speed(speed) {};

    IdPlayer addPlayer(IdSector idSector);

    bool transfer(Entity& e, IdSector destine, Position pos);
};

#endif
