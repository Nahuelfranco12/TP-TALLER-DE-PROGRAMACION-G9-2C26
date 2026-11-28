#include "mineral.h"

#include "../game_constants.h"
#include "../inventory/item.h"
#include "../inventory/mineral_item.h"
#include "../sectors/sector.h"
#include "./enemies/enemies_factory.h"

std::unique_ptr<Item> Mineral::toItem() const {
  double price = 0;
  switch (this->mineralType) {
  case MineralTypes::GOLD:
    price = PRICE_GOLD;
    break;
  case MineralTypes::IRON:
    price = PRICE_IRON;
    break;
  case MineralTypes::LAPIZLAZULI:
    price = PRICE_LAPIZLAZULI;
    break;
  case MineralTypes::COAL:
    price = PRICE_COAL;
    break;
  }
  return std::make_unique<MineralItem>(price, this->mineralType);
}

void Mineral::pickaxeEffect(Sector &sector, Position minerPosition) {
  if (std::rand() % 100 < hordeChance)
    sector.spawnHordeNear(minerPosition);
}

bool Mineral::breaks() const { 
  return std::rand() % 100 < breakChance; 
}
