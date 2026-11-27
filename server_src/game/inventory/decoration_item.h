#ifndef DECORATION_ITEM_H_
#define DECORATION_ITEM_H_

#include "item.h"
#include "placeable.h"

class DecorationItem : public Item, public Placeable {
private:
  FurnitureType decorationType;

public:
  DecorationItem(double price, FurnitureType decorationType)
      : Item(price, ItemType::FURNITURE, decorationType),
        decorationType(decorationType) {}

  bool canBePlacedAt(const Sector &sector, Position position) const override;
  std::unique_ptr<Entity> toEntity(Position position) const override;
};

#endif // DECORATION_ITEM_H_