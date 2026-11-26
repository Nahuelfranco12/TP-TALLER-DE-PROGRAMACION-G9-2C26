#ifndef SET_H_
#define SET_H_

#include "server_src/game/game_constants.h"
#include "../../world_state.h"

#include <cstddef>
#include <map>
#include <string>
#include <variant>
#include <vector>

struct GoalProgress {
  size_t target;
  size_t current = 0;
};

using GoalTypes = std::variant<AnimalType, CropTypes, EnemyType, MineralTypes, MoneyType>;

class Set {
public:
  virtual ~Set() = default;

  virtual bool complete(GoalTypes goal, size_t count) = 0;
  virtual bool isComplete() const = 0;
  virtual SetType type() const = 0;
  virtual SetState state() const = 0;
};

#endif // SET_H_
