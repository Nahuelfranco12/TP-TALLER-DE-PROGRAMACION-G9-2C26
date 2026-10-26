#include "inventory.h"

bool Inventory::addItem(std::unique_ptr<Item> item) {
    for (InventorySlot& slot : this->items) {
        if (slot.getItem().stacksWith(*item))
            return slot.add();
    }
    if (this->items.size() < MAX_INVENTORY_ITEMS) {
        this->items.emplace_back(std::move(item));
        return true;
    }
    return false;
}

bool Inventory::addTool(std::unique_ptr<Tool> tool) {
    for (auto& t : this->tools)
        if (t->toolType == tool->toolType)
            return false; // ya existe esa herramienta

    if (this->tools.size() < MAX_INVENTORY_TOOLS) {
        this->tools.emplace_back(std::move(tool));
        return true;
    }
    return false;
}

Tool* Inventory::getTool(AvailableTools type) {
    for (auto& t : this->tools)
        if (t->toolType == type)
            return t.get();
    return nullptr;
}
