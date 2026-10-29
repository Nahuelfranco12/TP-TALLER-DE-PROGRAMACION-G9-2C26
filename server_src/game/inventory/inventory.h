#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <list>
#include <memory>

#include "../game_constants.h"
#include "../world_state.h"
#include "inventory_slot.h"
#include "tool.h"

class Inventory {
private:
    std::list<InventorySlot> items;
    std::list<std::unique_ptr<Tool>> tools;

public:
    Inventory() : items(), tools() {}

    bool addItem(std::unique_ptr<Item> item);
    bool addTool(std::unique_ptr<Tool> tool);
    Tool* getTool(AvailableTools type);

    InventoryState state() const;
};

#endif // INVENTORY_H_
