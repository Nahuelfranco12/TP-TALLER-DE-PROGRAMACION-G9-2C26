#ifndef CROP_H_
#define CROP_H_

#include <cstddef>
#include <memory>

#include "../game_constants.h"
#include "../inventory/crop_item.h"
#include "collectable.h"
#include "crop_config.h"
#include "entity.h"
#include "waterable.h"
#include "../cheatable/growth_cheat.h"

class Crop : public Entity, public ICollectable, public IWaterable, public IGrowthCheat {
private:
  CropTypes type;
  const CropConfig &config;

  size_t growthTicks = 0;   // ticks que la planta creció
  size_t sinceWatered;      // ticks desde el último riego
  size_t thirstyTicks = 0;  // ticks que estuvo esperando agua
  size_t readyTicks = 0;    // ticks que estuvo lista sin ser recogida
  size_t extraHarvestsLeft;
  double luck;

  size_t totalGrowthTicks() const { return config.daysToGrow * TICKS_PER_DAY; }
  size_t waterIntervalTicks() const {
    return TICKS_PER_DAY / config.wateringsPerDay;
  }
  bool fullyGrown() const { return growthTicks >= totalGrowthTicks(); }

public:
  Crop(Position position, CropTypes type);

  CropGrowth growth() const;
  CropQuality quality() const;
  double price() const;

  /*
  * IWaterable
  */
  bool needsWater() const override;
  bool water() override;
  double waterEnergyCost() const override { return ENERGY_COST_WATER; }

  /*
  * ICollectable
  */
  bool canCollect() const override { return fullyGrown(); }
  std::unique_ptr<Item> collect() override;
  bool removeOnCollect() const override { return extraHarvestsLeft == 0; }
  double energyCost() const override { return ENERGY_COST_HARVEST_CROP; }

  /*
  * Cheat
  */
  void forceWater() { sinceWatered = 0; }

  /*
  * IGrowthCheat
  */
  void growthCheat() override { growthTicks = totalGrowthTicks(); }

  /*
  * Entity
  */
  void tick() override;
  EntityState entityState() const override;};

#endif // CROP_H_
