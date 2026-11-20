#ifndef MINERAL_ITEM_H_
#define MINERAL_ITEM_H_

#include "../game_constants.h"
#include "item.h"

class MineralItem : public Item {
public:
  MineralItem(double price, MineralTypes mineralType)
      : Item(price, ItemType::MINERAL, mineralType) {}

  bool stacksWith(const Item &other) const override;

  std::unique_ptr<Item> clone() const override {
    return std::make_unique<MineralItem>(*this);
  }
};

#endif // MINERAL_ITEM_H_
