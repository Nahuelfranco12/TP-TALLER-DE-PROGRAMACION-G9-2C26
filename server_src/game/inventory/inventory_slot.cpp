#include "inventory_slot.h"

Item &InventorySlot::getItem() const { return *this->item; }

size_t InventorySlot::getCount() const { return this->count; }

void InventorySlot::add(size_t amount) {
  count += amount;
}

bool InventorySlot::remove() {
  if (this->count == 0)
    return false;
  this->count--;
  return true;
}
