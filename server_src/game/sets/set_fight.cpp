#include "set_fight.h"

#include "server_src/game/game_constants.h"

#include <stdexcept>

SetFight::SetFight()
    : goals({{EnemyType::SKELETON, {SET_FIGHT_COUNT_SKELETON, 0}},
             {EnemyType::VAMPIRE_MALE, {SET_FIGHT_COUNT_VAMPIRE, 0}},
             {EnemyType::ORC, {SET_FIGHT_COUNT_ORC, 0}},
             {EnemyType::SKULL_BLUE, {SET_FIGHT_COUNT_SKULL, 0}}}) {}

EnemyType SetFight::canonical(EnemyType type) const {
  if (type == EnemyType::VAMPIRE_FEMALE)
    return EnemyType::VAMPIRE_MALE;
  if (type == EnemyType::SKULL_GREEN)
    return EnemyType::SKULL_BLUE;
  return type;
}

bool SetFight::checkComplete() {
  for (const auto &[type, goal] : goals) {
    if (goal.current < goal.target)
      return false;
  }
  return true;
}

bool SetFight::complete(GoalTypes goal, size_t count) {
  if (completed)
    return true;

  EnemyType goalType;
  try {
    goalType = std::get<EnemyType>(goal);
  } catch (const std::bad_variant_access &) {
    return false;
  }

  goalType = canonical(goalType);
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

SetState SetFight::state() const {
  SetState result;
  result.type = static_cast<int>(SetType::FIGHT);
  result.completed = completed;
  for (const auto &[type, goal] : goals) {
    result.goals.push_back({static_cast<int>(type), goal.current, goal.target});
  }
  return result;
}