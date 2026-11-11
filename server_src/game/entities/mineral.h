#ifndef MINERAL_H_
#define MINERAL_H_

#include <memory>

#include "../game_constants.h"
#include "../inventory/item.h"
#include "entity.h"
#include "hittable.h"

class Mineral : public Entity, public Hittable {
private:
  MineralTypes mineralType;

  double spawnFrequency;

public:
  Mineral(size_t pos_x, size_t pos_y, MineralTypes mineralType,
          double spawnFrequency, size_t pickaxeHits)
      : Entity(pos_x, pos_y, EntityTypes::MINERAL), Hittable(pickaxeHits),
        mineralType(mineralType), spawnFrequency(spawnFrequency) {}

  MineralTypes getMineralType() const { return mineralType; }
  double getSpawnFrequency() const { return spawnFrequency; }

  std::unique_ptr<Item> toItem() const;
  void pickaxeEffect();

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.mineral.type = this->mineralType;
    return state;
  }
};

#endif // MINERAL_H_
