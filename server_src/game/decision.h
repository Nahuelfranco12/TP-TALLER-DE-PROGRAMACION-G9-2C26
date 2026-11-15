#ifndef DECISION_H_
#define DECISION_H_

#include "../../common_src/game_dtos.h"

enum class DecisionType {NONE, MOVE, ATTACK};

struct Decision {
    DecisionType type = DecisionType::NONE;
    DirectionDto direction{};
};

#endif // DECISION_H_