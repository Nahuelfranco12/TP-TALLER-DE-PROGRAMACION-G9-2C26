#include "inventory.h"
#include "crop_item.h"
#include <utility>

bool Inventory::receive(InventorySlot &slot) {
  for (InventorySlot &mine : items) {
    bool isTheSameItem = mine.getItem().stacksWith(slot.getItem());
    bool fitsInSlot = mine.getCount() + slot.getCount() <= maxStack;
    if (isTheSameItem && fitsInSlot) {
      mine.add(slot.getCount());
      return true;
    }
  }
  if (items.size() < maxSlots) {
    items.push_back(std::move(slot));
    return true;
  }
  return false;
}

bool Inventory::addItem(std::unique_ptr<Item> item) {
  if (!item)
    return false;
  InventorySlot slot(std::move(item));
  return receive(slot);
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

bool Inventory::giveSlotTo(int index, Inventory &other) {
  if (index < 0 || index >= static_cast<int>(items.size()))
    return false;
  auto it = items.begin();
  std::advance(it, index);
  
  if (!it->getItem().isTransferable())
    return false;

  if (!other.receive(*it))
    return false;
  items.erase(it);
  return true;
}

int Inventory::countOf(const Item &sample) const {
  int total = 0;
  for (const InventorySlot &slot : this->items)
    if (slot.getItem().isSameProduct(sample))
      total += static_cast<int>(slot.getCount());
  return total;
}

bool Inventory::remove(const Item &sample, int amount,  double &multipliers) {
  if (amount <= 0 || countOf(sample) < amount)
    return false;

  multipliers = 0;
  auto it = this->items.begin();
  while (it != this->items.end() && amount > 0) {
    if (!it->getItem().isSameProduct(sample)) {
      it++;
    } else {
      multipliers += it->getItem().priceMultiplier();
      it->remove();
      amount--;
      if (it->getCount() == 0)
        it = this->items.erase(it);
    }
  }
  return true;
}

bool Inventory::remove(const Item &sample, int amount) {
  double ignored = 0;
  return remove(sample, amount, ignored);
}


const Item *Inventory::itemAt(int index) const {
  if (index < 0 || index >= static_cast<int>(items.size()))
    return nullptr;
  auto it = items.begin();
  std::advance(it, index);
  return &it->getItem();
}

bool Inventory::removeFromSlot(int index) {
  if (index < 0 || index >= static_cast<int>(items.size()))
    return false;
  auto it = items.begin();
  std::advance(it, index); 
  it->remove();
  if (it->getCount() == 0)
    items.erase(it);
  return true;
}