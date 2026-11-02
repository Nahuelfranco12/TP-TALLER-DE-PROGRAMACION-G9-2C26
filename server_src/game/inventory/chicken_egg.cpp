#include "chicken_egg.h"

bool ChickenEgg::stacksWith(const Item& other) const {
    if (this->getType() != other.getType())
        return false;
    
    const ChickenEgg* o = dynamic_cast<const ChickenEgg*>(&other);
    
    if (!o)
        return false;
    return this->getSubtype() == o->getSubtype();
}