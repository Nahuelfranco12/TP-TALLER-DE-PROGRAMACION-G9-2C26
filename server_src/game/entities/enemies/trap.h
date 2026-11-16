#ifndef TRAP_H_
#define TRAP_H_

#include "../../game_constants.h"
#include "entity.h"

class Trap : public Entity {
private:
  size_t timeTicks;

public:
  Trap(size_t pos_x, size_t pos_y, size_t timeTicks)
      : Entity(pos_x, pos_y, EntityTypes::ENEMY), timeTicks(timeTicks) {}
};

#endif // TRAP_H_
