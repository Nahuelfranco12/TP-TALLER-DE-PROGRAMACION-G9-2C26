#include "inventory.h"
#include "crop_item.h"
#include <utility>

bool Inventory::addItem(std::unique_ptr<Item> item) {
  if (!item) return false;
  for (InventorySlot &slot : this->items) {
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
  // cppcheck-suppress useStlAlgorithm
  for (const auto &t : this->tools)
    if (t->toolType == tool->toolType)
      return false; // ya existe esa herramienta

  if (this->tools.size() < MAX_INVENTORY_TOOLS) {
    this->tools.emplace_back(std::move(tool));
    return true;
  }
  return false;
}

Tool *Inventory::getTool(AvailableTools type) {
  for (auto &t : this->tools)
    // cppcheck-suppress useStlAlgorithm
    if (t->toolType == type)
      return t.get();
  return nullptr;
}

InventoryState Inventory::state() const {
  InventoryState state;
  state.items.reserve(items.size());
  for (const InventorySlot &slot : items) {
    const Item &item = slot.getItem();
    ItemState itemState;
    itemState.type = item.getType();
    itemState.subtype = item.subtypeToInt();
    itemState.count = slot.getCount();
    const CropItem *crop = dynamic_cast<const CropItem *>(&item);
        if (crop) {
            itemState.quality = crop->getQuality();
        }

        state.items.push_back(itemState);
    
  }
  for (const auto &tool : tools)
    state.tools.push_back({tool->toolType});
  return state;
}
