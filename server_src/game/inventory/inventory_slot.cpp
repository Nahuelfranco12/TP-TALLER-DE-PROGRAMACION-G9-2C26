#include "inventory_slot.h"

Item &InventorySlot::getItem() const { return *this->item; }

size_t InventorySlot::getCount() const { return this->count; }

bool InventorySlot::add() {
  if (this->count < MAX_INVETORY_STACK) {
    this->count++;
    return true;
  }
  return false;
}
