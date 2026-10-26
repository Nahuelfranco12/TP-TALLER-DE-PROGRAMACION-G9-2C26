#include "inventory_slot.h"

Item& InventorySlot::getItem() { return this->item; }

size_t InventorySlot::getCount() { return this->count; }

bool InventorySlot::addItem() {
    if (this->count < MAX_INVETORY_STACK) { 
        this->count++;
        return true;
    }
    return false;
}
