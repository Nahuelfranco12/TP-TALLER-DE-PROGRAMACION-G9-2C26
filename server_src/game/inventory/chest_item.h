#ifndef CHEST_ITEM_H_
#define CHEST_ITEM_H_

#include "item.h"
#include "placeable.h"

class ChestItem : public Item, public Placeable {
public:
explicit ChestItem(double price)
    : Item(price, ItemType::FURNITURE, FurnitureType::CHEST) {}
    
  bool canBePlacedAt(const Sector &sector, Position position) const override;
  std::unique_ptr<Entity> toEntity(Position position) const override;
};

#endif // CHEST_ITEM_H_