#include "set_animal.h"

#include "server_src/game/game_constants.h"

#include <stdexcept>

SetAnimal::SetAnimal()
    : goals({{AnimalType::COW, {SET_ANIMALS_COUNT_MILK, 0}},
             {AnimalType::CHICKEN, {SET_ANIMALS_COUNT_EGG, 0}}}) {}

bool SetAnimal::checkComplete() {
  for (const auto &[type, goal] : goals) {
    if (goal.current < goal.target)
      return false;
  }
  return true;
}

bool SetAnimal::complete(GoalTypes goal, size_t count) {
  if (completed)
    return true;

  AnimalType goalType;
  try {
    goalType = std::get<AnimalType>(goal);
  } catch (const std::bad_variant_access &) {
    return false;
  }

  auto it = goals.find(goalType);
  if (it == goals.end())
    return false;

  GoalProgress &progress = it->second;
  progress.current += count;
  if (progress.current > progress.target)
    progress.current = progress.target;

  if (checkComplete()) {
    completed = true;
    return true;
  }
  return false;
}

SetState SetAnimal::state() const {
  SetState result;
  result.type = static_cast<int>(SetType::ANIMAL);
  result.completed = completed;
  for (const auto &[type, goal] : goals) {
    result.goals.push_back({static_cast<int>(type), goal.current, goal.target});
  }
  return result;
}
