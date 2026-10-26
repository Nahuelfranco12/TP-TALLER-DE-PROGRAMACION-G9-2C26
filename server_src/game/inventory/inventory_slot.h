#ifndef INVENTORY_SLOT_H_
#define INVENTORY_SLOT_H_

#include <cstdlib>
#include <memory>

#include "../game_constants.h"
#include "item.h"

class InventorySlot {
private:
    std::unique_ptr<Item> item;
    size_t count;

public:
    explicit InventorySlot(std::unique_ptr<Item> item) : item(std::move(item)), count(1) {}

    Item& getItem();
    size_t getCount();
    bool add();
};

#endif // INVENTORY_SLOT_H_
