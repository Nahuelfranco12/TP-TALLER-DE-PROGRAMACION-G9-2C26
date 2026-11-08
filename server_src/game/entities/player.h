#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <memory>
#include <utility>

#include "../../world_state.h"
#include "../game_constants.h"
#include "../inventory/inventory.h"
#include "../move_result.h"
#include "entity.h"
#include "player_outfit.h"
#include "../inventory/seed.h"

class Sector;  // forward declaration
class Mineral; // forward declaration

class Player : public Entity {
private:
  int id;
  double life;
  double energy;
  int coins;
  PlayerOutfit outfit;

  Tool *actualTool = nullptr;
  Inventory inventory;
  Sector *actualSector;

public:
  Player(size_t pos_x, size_t pos_y, int id, Sector *actualSector,
         PlayerOutfit outfit)
      : Entity(pos_x, pos_y, EntityTypes::PLAYER), id(id), life(100),
        energy(100), coins(rand() % 100 + 1), outfit(outfit), inventory(),
        actualSector(actualSector) {
    this->inventory.addTool(std::make_unique<Tool>(AvailableTools::PICKAXE));
    this->inventory.addTool(std::make_unique<Tool>(AvailableTools::SWORD));
    this->inventory.addTool(std::make_unique<Tool>(AvailableTools::SHOVEL));
    this->inventory.addTool(
        std::make_unique<Tool>(AvailableTools::WATERING_CAN));
    
    for (int i = 0; i < 5; i++) {
      this->inventory.addItem(std::make_unique<Seed>(10, CropTypes::STRAWBERRY));
    }

    this->actualTool = this->inventory.getTool(AvailableTools::PICKAXE);
  }

  MoveResult move(Position destination);
  void mine(Mineral &mineral);

  void selectTool(AvailableTools tool);
  Tool *getSelectedTool();

  // getters
  Sector *getActualSector() { return actualSector; }
  void setActualSector(Sector *s) { actualSector = s; }
  double getLife() const { return life; }
  double getEnergy() const { return energy; }
  size_t getCoins() const { return coins; }
  Inventory &getInventory() { return inventory; }

  // state para el serializar el estado del mundo
  PlayerState state() const;
  EntityState entityState() const override {
    EntityState entity_state = Entity::entityState();
    entity_state.playerId = id;
    return entity_state;
  }
};

#endif // PLAYER_H_
