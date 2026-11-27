#include "set_gold.h"

#include "server_src/game/game_constants.h"

#include <stdexcept>

SetGold::SetGold()
    : goals({{MoneyType::GOLD, {SET_MONEY_COUNT_GOLD, 0}}}) {}

bool SetGold::checkComplete() {
  for (const auto &[type, goal] : goals) {
    if (goal.current < goal.target)
      return false;
  }
  return true;
}

bool SetGold::complete(GoalTypes goal, size_t count) {
  (void)goal;
  if (completed)
    return true;

  auto it = goals.find(MoneyType::GOLD);
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

SetState SetGold::state() const {
  SetState result;
  result.type = static_cast<int>(SetType::MONEY);
  result.completed = completed;
  for (const auto &[type, goal] : goals) {
    result.goals.push_back({static_cast<int>(type), goal.current, goal.target});
  }
  return result;
}