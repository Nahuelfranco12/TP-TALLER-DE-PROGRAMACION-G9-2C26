#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>

#include "entity.h"
#include "../position.h"
#include "../inventory/inventory.h"
#include "mineral.h"
#include "sector.h"

class Player : public Entity {
private:
    double life = 100;
    double energy = 100;
    size_t coins;
    Inventory inventory;
    Sector& actualSector;

public:
    Player(size_t pos_x, size_t pos_y, Sector& actualSector) : Entity(pos_x, pos_y), coins(rand() % 100 + 1), inventory(), actualSector(actualSector) {};

    /*
    * Mines a mineral, then stores the MineralItem obtained on the Invetory.
    */
    void mine(Mineral& mineral);
};

#endif // PLAYER_H_
