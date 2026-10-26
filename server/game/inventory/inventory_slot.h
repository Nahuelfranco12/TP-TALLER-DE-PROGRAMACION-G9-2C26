#ifndef INVENTORY_SLOT_H_
#define INVENTORY_SLOT_H_

#include <cstdlib>

#include "item.h"
#include "../game_constants.h"

class InventorySlot {
    Item item;
    size_t count = 0;
public:
    InventorySlot(Item item) : item(item) {};

    Item& getItem();
    size_t getCount();
    bool addItem();
};

#endif // INVENTORY_SLOT_H_
