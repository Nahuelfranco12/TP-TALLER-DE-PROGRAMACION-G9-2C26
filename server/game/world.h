#ifndef WORLD_H_
#define WORLD_H_

#include <map>
#include <list>

#include "id_sector.h"
#include "sector.h"
#include "player.h"

class World {
private:
    double speed;

    std::map<IdSector, Sector> sectors;
    std::list<Player> players;

public:
    World();

    bool transfer(Entity& e, IdSector destine, Position pos);
};

#endif
