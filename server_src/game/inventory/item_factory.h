#ifndef ITEM_FACTORY_H_
#define ITEM_FACTORY_H_

#include <memory>

#include "item.h"

class ItemFactory {
public:
  std::unique_ptr<Item> create(ItemType type, int subtype, int price, CropQuality quality = CropQuality::BASE) const;
};

#endif // ITEM_FACTORY_H_