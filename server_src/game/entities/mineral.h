#ifndef MINERAL_H_
#define MINERAL_H_

#include <memory>

#include "../game_constants.h"
#include "../inventory/item.h"
#include "entity.h"
#include "hittable.h"

class Sector;

class Mineral : public Entity, public Hittable {
private:
  MineralTypes mineralType;

  double spawnFrequency;
  int breakChance;
  int hordeChance;

public:
  Mineral(size_t pos_x, size_t pos_y, MineralTypes mineralType,
          double spawnFrequency, size_t pickaxeHits, int breakChance, int hordeChance)
      : Entity(pos_x, pos_y, EntityTypes::MINERAL), Hittable(pickaxeHits),
        mineralType(mineralType), spawnFrequency(spawnFrequency), breakChance(breakChance), hordeChance(hordeChance) {}

  MineralTypes getMineralType() const { return mineralType; }
  double getSpawnFrequency() const { return spawnFrequency; }

  std::unique_ptr<Item> toItem() const;
  void pickaxeEffect(Sector &sector, Position minerPosition);

  bool breaks() const;

  EntityState entityState() const override {
    EntityState state = Entity::entityState();
    state.mineral.type = this->mineralType;
    state.mineral.remainingHits = this->getHitsLeft();
    return state;
  }
};

#endif // MINERAL_H_
