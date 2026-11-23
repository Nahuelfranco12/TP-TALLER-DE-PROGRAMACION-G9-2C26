#ifndef BED_ITEM_H_
#define BED_ITEM_H_

#include "item.h"
#include "placeable.h"

class BedItem : public Item, public Placeable {
private:
  int ownerId;

public:
  explicit BedItem(int ownerId)
      : Item(0, ItemType::FURNITURE, FurnitureType::BED), ownerId(ownerId) {}

  bool canBePlacedAt(const Sector &sector, Position position) const override;
  std::unique_ptr<Entity> toEntity(Position position) const override;
};

#endif // BED_ITEM_H_