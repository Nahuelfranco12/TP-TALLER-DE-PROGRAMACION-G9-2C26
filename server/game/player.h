#ifndef PLAYER_H_
#define PLAYER_H_

#include "position.h"
#include "inventory.h"
#include "mineral.h"
#include "sector.h"

class Player {
private:
    double life;
    double energy;
    int coins;
    Inventory inventory;
    Sector& actualSector;

public:
    Position move(Position destination);

    /*
    * Mines a mineral, then stores the MineralItem obtained on the Invetory.
    */
    void mine(Mineral& mineral);
};

#endif // PLAYER_H_
