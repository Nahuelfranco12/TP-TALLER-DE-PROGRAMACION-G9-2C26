#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <list>

#include "id_sector.h"
#include "sector.h"
#include "./entities/player.h"

class World {
private:
    double speed;

    std::map<IdSector, Sector> sectors;
    std::list<Player> players;

public:
    World();

    void addSector(IdSector id);
    void addPlayer(Player player);

    bool transfer(Entity& e, IdSector destine, Position pos);
};

#endif
