#ifndef SET_FIGHT_H_
#define SET_FIGHT_H_

#include "server_src/game/game_constants.h"
#include "server_src/game/sets/set.h"

#include <cstddef>
#include <map>

class SetFight : public Set {
private:
  std::map<EnemyType, GoalProgress> goals;
  bool completed = false;

  EnemyType canonical(EnemyType type) const;
  bool checkComplete();

public:
  SetFight();

  bool complete(GoalTypes goal, size_t count) override;
  bool isComplete() const override { return completed; }
  SetType type() const override { return SetType::FIGHT; }
  SetState state() const override;
};

#endif // SET_FIGHT_H_
