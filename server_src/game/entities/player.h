#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <memory>

#include "../world_state.h"
#include "../inventory/inventory.h"
#include "../move_result.h"
#include "entity.h"

class Sector;  // forward declaration
class Mineral; // forward declaration

class Player : public Entity {
private:
    int id;
    double life;
    double energy;
    size_t coins;
    Inventory inventory;
    Sector* actualSector;

public:
    Player(size_t pos_x, size_t pos_y, int id, Sector* actualSector) : Entity(pos_x, pos_y, EntityTypes::PLAYER), id(id), life(100), energy(100), coins(rand() % 100 + 1), inventory(), actualSector(actualSector) {}

    MoveResult move(Position destination);
    void mine(Mineral& mineral);

    Sector* getActualSector() { return actualSector; }
    void setActualSector(Sector* s) { actualSector = s; }
    double getLife() const { return life; }
    double getEnergy() const { return energy; }
    size_t getCoins() const { return coins; }
    Inventory& getInventory() { return inventory; }

    PlayerState state() const;

    EntityState entityState() const override {
        EntityState state = Entity::entityState();
        state.playerId = id;
        return state;
    }
};

#endif // PLAYER_H_
