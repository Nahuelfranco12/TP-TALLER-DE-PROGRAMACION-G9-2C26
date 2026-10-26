#include "inventory.h"

bool Inventory::addItem(Item& item) {
    // elemento ya en el inventario
    for (InventorySlot slot : this->items) {
        if (&slot.getItem() == &item)
            return slot.addItem();
    }

    if (this->items.size() < MAX_INVENTORY_ITEMS) {
        this->items.emplace(this->items.begin(), item);
        return true;
    }
    return false;
}

bool Inventory::addTool(Tool& tool) {
    if (this->tools.size() < MAX_INVENTORY_TOOLS)
        return false;
    for (Tool inventoryTool : this->tools)
        if (&inventoryTool != &tool) {
            this->tools.emplace(this->tools.begin(), tool);
            return true;
        }
    return false;
}
