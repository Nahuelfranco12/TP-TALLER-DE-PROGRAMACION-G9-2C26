#ifndef DECISION_H_
#define DECISION_H_

#include "../../common_src/game_dtos.h"
#include "position.h"

#include <optional>

enum class DecisionType { NONE, MOVE, ATTACK };

struct Decision {
  DecisionType type = DecisionType::NONE;
  DirectionDto direction{};
  std::optional<Position> target;
};

#endif // DECISION_H_