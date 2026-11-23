#ifndef PLACEABLE_H_
#define PLACEABLE_H_

#include <memory>

#include "../position.h"

class Entity;
class Sector;

class Placeable {
public:
  virtual ~Placeable() = default;

  virtual bool canBePlacedAt(const Sector &sector, Position position) const = 0;

  virtual std::unique_ptr<Entity> toEntity(Position position) const = 0;
};

#endif // PLACEABLE_H_