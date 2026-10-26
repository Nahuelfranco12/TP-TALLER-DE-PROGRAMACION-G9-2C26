#ifndef INVENTORY_H_
#define INVENTORY_H_

#include "inventory_slot.h"
#include "tool.h"
#include "../game_constants.h"

#include <list>

class Inventory {
private:
    std::list<InventorySlot> items;
    std::list<Tool> tools;

public:
    Inventory() : items(), tools() {};

    bool addItem(Item& item);
    bool addTool(Tool& tool);

    Tool& getPickaxe();
    Tool& getSword();
    Tool& getShovel();
    Tool& getWateringCan();
};

#endif // INVENTORY_H_
