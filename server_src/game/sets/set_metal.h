#ifndef SET_METAL_H_
#define SET_METAL_H_

#include "server_src/game/game_constants.h"
#include "server_src/game/sets/set.h"

#include <cstddef>
#include <map>

class SetMetal : public Set {
private:
  std::map<MineralTypes, GoalProgress> goals;
  bool completed = false;

  bool checkComplete();

public:
  SetMetal();

  bool complete(GoalTypes goal, size_t count) override;
  bool isComplete() const override { return completed; }
  SetType type() const override { return SetType::METAL; }
  SetState state() const override;
};

#endif // SET_METAL_H_
