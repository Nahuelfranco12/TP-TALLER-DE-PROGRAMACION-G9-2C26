#include "cow_milk.h"

bool CowMilk::stacksWith(const Item& other) const {
    if (this->getType() != other.getType())
        return false;
    
    const CowMilk* o = dynamic_cast<const CowMilk*>(&other);
    
    if (!o)
        return false;
    return this->type == o->type;
}