#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#include <memory>
#include "../inventory/item.h"

class ICollectable {
public:
    virtual ~ICollectable() = default;
 
    virtual bool canCollect() const = 0;
 
    virtual std::unique_ptr<Item> collect() = 0;
};

#endif // COLLECTABLE_H_
