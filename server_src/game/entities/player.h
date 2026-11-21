#ifndef PLAYER_H_
#define PLAYER_H_

#include <cstdlib>
#include <memory>
#include <utility>

#include "../../world_state.h"
#include "../game_constants.h"
#include "../inventory/inventory.h"
#include "../inventory/seed.h"
#include "../move_result.h"
#include "entity.h"
#include "player_outfit.h"

class Sector;  // forward declaration
class Mineral; // forward declaration
class Enemy;   // forward declaration
class Merchant; // forward declaration

struct PendingGift {
  int giverId = 0;
  int slotIndex = 0;
  ItemState item{};
};

class Player : public Entity {
private:
  int id;
  std::string name;
  double life;
  double energy;
  int coins;
  PlayerOutfit outfit;

  Tool *actualTool = nullptr;
  Merchant *talkingTo = nullptr;
  PendingGift pendingGift{};
  Inventory inventory;
  Sector *actualSector;

public:
  Player(size_t pos_x, size_t pos_y, int id, const std::string &name,
         Sector *actualSector, PlayerOutfit outfit, int coins = (rand() % 100 + 1))
      : Entity(pos_x, pos_y, EntityTypes::PLAYER), id(id), name(name),
        life(100), energy(100), coins(coins), outfit(outfit),
        inventory(), actualSector(actualSector) {
    this->inventory.addTool(std::make_unique<Tool>(AvailableTools::PICKAXE));
    this->inventory.addTool(std::make_unique<Tool>(AvailableTools::SWORD));
    this->inventory.addTool(std::make_unique<Tool>(AvailableTools::SHOVEL));
    this->inventory.addTool(
        std::make_unique<Tool>(AvailableTools::WATERING_CAN));

    for (int i = 0; i < 5; i++) {
      this->inventory.addItem(
          std::make_unique<Seed>(10, CropTypes::STRAWBERRY));
    }

    this->actualTool = this->inventory.getTool(AvailableTools::PICKAXE);
  }

  void setCoins(int coins) {
    if (coins >= 0)
      this->coins = coins;
  }

  MoveResult move(Position destination);
  void mine(Mineral &mineral);
  void attack(Enemy &enemy);
  void selectTool(AvailableTools tool);

  // getters
  Tool *getSelectedTool();
  int getId() const { return id; }
  const std::string &getName() const { return name; }
  Sector *getActualSector() { return actualSector; }
  void setActualSector(Sector *s) { actualSector = s; }
  double getLife() const { return life; }
  double getEnergy() const { return energy; }
  size_t getCoins() const { return coins; }
  Inventory &getInventory() { return inventory; }

  /*
  * Regalos
  */
  bool hasPendingGift() const { return pendingGift.item.count > 0; }
  const PendingGift &getPendingGift() const { return pendingGift; }
  void setPendingGift(const PendingGift &gift) { pendingGift = gift; }
  void clearPendingGift() { pendingGift = PendingGift{}; }

  /*
  * Energia
  */
  bool hasEnergy(size_t cost);
  bool spendEnergy(size_t cost);
  void setLife(double value);
  void setEnergy(double value);
  void restoreEnergy(size_t amount);
  bool isBadlyHurt() const;

  /*
  * Daño
  */
  void takeDamage(double amount);
  bool isUnconscious() const { return life <= 0; }

  void startNewDay(bool sleptInBed);

  /*
  * Tradeo
  */
  int buy(const Item &sample, int price, int amount);
  bool sell(const Item &sample, int price, int amount);
  
  void startTalkingTo(Merchant &merchant) { talkingTo = &merchant; }
  Merchant *getTalkingTo() const { return talkingTo; }

  /*
  * State
  */
  PlayerState state() const;
  EntityState entityState() const override {
    EntityState entity_state = Entity::entityState();
    entity_state.playerId = id;
    return entity_state;
  }
};

#endif // PLAYER_H_
