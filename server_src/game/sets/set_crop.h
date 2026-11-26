#ifndef SET_CROP_H_
#define SET_CROP_H_

#include "server_src/game/game_constants.h"
#include "server_src/game/sets/set.h"

#include <cstddef>
#include <map>

class SetCrop : public Set {
private:
  std::map<CropTypes, GoalProgress> goals;
  bool completed = false;

  bool checkComplete();

public:
  SetCrop();

  bool complete(GoalTypes goal, size_t count) override;
  bool isComplete() const override { return completed; }
  SetType type() const override { return SetType::CROP; }
  SetState state() const override;
};

#endif // SET_CROP_H_
