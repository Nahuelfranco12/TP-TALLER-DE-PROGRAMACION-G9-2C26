#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"
#include "../position.h"
#include "../inventory/inventory.h"
#include "mineral.h"
#include "sector.h"

class Player : public Entity {
private:
    double life = 100;
    double energy = 100;
    int coins;
    Inventory inventory;
    Sector& actualSector;

public:
    Player();

    Position move(Position destination);

    /*
    * Mines a mineral, then stores the MineralItem obtained on the Invetory.
    */
    void mine(Mineral& mineral);
};

#endif // PLAYER_H_
