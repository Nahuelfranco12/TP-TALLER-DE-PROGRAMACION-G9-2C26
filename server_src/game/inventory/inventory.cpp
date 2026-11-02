#include "inventory.h"

bool Inventory::addItem(std::unique_ptr<Item> item) {
    for (InventorySlot& slot : this->items) {
        if (slot.getItem().stacksWith(*item)) {
            bool result = slot.add();
            if (result)
                return true;
        }
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

InventoryState Inventory::state() const {
    InventoryState state;
    state.items.reserve(items.size());
    for (const InventorySlot& slot : items) {
        const Item& item = slot.getItem();
        state.items.push_back({item.getType(), item.subtypeToInt(),
                           static_cast<uint8_t>(slot.getCount())});
    }
    for (const auto& tool : tools)
        state.tools.push_back({tool->toolType});
    return state;
}