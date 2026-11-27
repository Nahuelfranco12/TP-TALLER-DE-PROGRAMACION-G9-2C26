#ifndef SET_GOLD_H_
#define SET_GOLD_H_

#include "server_src/game/game_constants.h"
#include "server_src/game/sets/set.h"

#include <cstddef>
#include <map>

class SetGold : public Set {
private:
  std::map<MoneyType, GoalProgress> goals;
  bool completed = false;

  bool checkComplete();

public:
  SetGold();

  bool complete(GoalTypes goal, size_t count) override;
  bool isComplete() const override { return completed; }
  SetType type() const override { return SetType::MONEY; }
  SetState state() const override;
};

#endif // SET_GOLD_H_
