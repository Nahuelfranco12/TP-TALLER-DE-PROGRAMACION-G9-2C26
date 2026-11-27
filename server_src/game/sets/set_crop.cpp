#include "set_crop.h"

#include "server_src/game/game_constants.h"

#include <stdexcept>

SetCrop::SetCrop()
    : goals({{CropTypes::STRAWBERRY, {SET_CROP_COUNT_STRAWBERRY, 0}},
             {CropTypes::GREEN_ONION, {SET_CROP_COUNT_GREEN_ONION, 0}},
             {CropTypes::POTATO, {SET_CROP_COUNT_POTATO, 0}},
             {CropTypes::PUMPKIN, {SET_CROP_COUNT_PUMPKIN, 0}}}) {}

bool SetCrop::checkComplete() {
  for (const auto &[type, goal] : goals) {
    if (goal.current < goal.target)
      return false;
  }
  return true;
}

bool SetCrop::complete(GoalTypes goal, size_t count) {
  if (completed)
    return true;

  CropTypes goalType;
  try {
    goalType = std::get<CropTypes>(goal);
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

SetState SetCrop::state() const {
  SetState result;
  result.type = static_cast<int>(SetType::CROP);
  result.completed = completed;
  for (const auto &[type, goal] : goals) {
    result.goals.push_back({static_cast<int>(type), goal.current, goal.target});
  }
  return result;
}