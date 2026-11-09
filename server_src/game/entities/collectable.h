#ifndef COLLECTABLE_H_
#define COLLECTABLE_H_

#include "../inventory/item.h"
#include <memory>

class ICollectable {
public:
  virtual ~ICollectable() = default;

  virtual bool canCollect() const = 0;

  virtual std::unique_ptr<Item> collect() = 0;

  virtual bool removeOnCollect() const = 0;

  virtual double energyCost() const = 0;
};

#endif // COLLECTABLE_H_
