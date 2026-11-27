#ifndef SET_ANIMAL_H_
#define SET_ANIMAL_H_

#include "server_src/game/game_constants.h"
#include "server_src/game/sets/set.h"

#include <cstddef>
#include <map>

class SetAnimal : public Set {
private:
  std::map<AnimalType, GoalProgress> goals;
  bool completed = false;

  bool checkComplete();

public:
  SetAnimal();

  bool complete(GoalTypes goal, size_t count) override;
  bool isComplete() const override { return completed; }
  SetType type() const override { return SetType::ANIMAL; }
  SetState state() const override;
};

#endif // SET_ANIMAL_H_
