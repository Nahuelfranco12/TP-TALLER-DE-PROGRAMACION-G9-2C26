#include "mineral_item.h"

bool MineralItem::stacksWith(const Item& other) const {
    if (this->getType() != other.getType())
        return false;
    
    const MineralItem* o = dynamic_cast<const MineralItem*>(&other);
    
    if (!o)
        return false;
    return this->getSubtype() == o->getSubtype();
}
