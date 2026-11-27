#include "set_metal.h"

#include "server_src/game/game_constants.h"

#include <stdexcept>

SetMetal::SetMetal()
    : goals({{MineralTypes::COAL, {SET_METALS_COUNT_COAL, 0}},
             {MineralTypes::LAPIZLAZULI, {SET_METALS_COUNT_LAPIZLAZULI, 0}},
             {MineralTypes::IRON, {SET_METALS_COUNT_IRON, 0}},
             {MineralTypes::GOLD, {SET_METALS_COUNT_GOLD, 0}}}) {}

bool SetMetal::checkComplete() {
  for (const auto &[type, goal] : goals) {
    if (goal.current < goal.target)
      return false;
  }
  return true;
}

bool SetMetal::complete(GoalTypes goal, size_t count) {
  if (completed)
    return true;

  MineralTypes goalType;
  try {
    goalType = std::get<MineralTypes>(goal);
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

SetState SetMetal::state() const {
  SetState result;
  result.type = static_cast<int>(SetType::METAL);
  result.completed = completed;
  for (const auto &[type, goal] : goals) {
    result.goals.push_back({static_cast<int>(type), goal.current, goal.target});
  }
  return result;
}