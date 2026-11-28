#include "set_fight.h"

#include "server_src/game/entities/enemies/vampire.h"
#include "server_src/game/game_constants.h"

#include <algorithm>

SetFight::SetFight() {}

int cavernLevel(IdSector sector) {
  if (sector < IdSector::CAVERN_LEVEL_1 || sector > IdSector::CAVERN_LEVEL_10)
    return -1;
  return static_cast<int>(sector) - static_cast<int>(IdSector::CAVERN_LEVEL_1) + 1;
}

size_t SetFight::consecutiveSkeletonCount() const {
  std::set<int> levels;
  for (IdSector room : skeletonSectors) {
    int level = cavernLevel(room);
    if (level > 0)
      levels.insert(level);
  }

  size_t longestStreak = 0;
  size_t currentStreak = 0;
  int previousLevel = 0;
  bool first = true;

  for (int level : levels) {
    if (first || level == previousLevel + 1) {
      currentStreak++;
    } else {
      currentStreak = 1;
    }

    longestStreak = std::max(longestStreak, currentStreak);
    previousLevel = level;
    first = false;
  }

  return std::min(longestStreak, static_cast<size_t>(SET_FIGHT_COUNT_SKELETON));
}

size_t SetFight::completedVampireCount() const {
  return std::min(completedVampirePairs.size() * SET_FIGHT_COUNT_VAMPIRE,
                 static_cast<size_t>(SET_FIGHT_COUNT_VAMPIRE));
}

size_t SetFight::bestOrcGroupCount() const {
  size_t best = 0;
  for (const auto &[group, kills] : orcGroupKills) {
    best = std::max(best, static_cast<size_t>(kills));
  }
  return std::min(best, static_cast<size_t>(SET_FIGHT_COUNT_ORC));
}

bool SetFight::checkComplete() {
  if (consecutiveSkeletonCount() >= SET_FIGHT_COUNT_SKELETON &&
      completedVampireCount() >= SET_FIGHT_COUNT_VAMPIRE &&
      bestOrcGroupCount() >= SET_FIGHT_COUNT_ORC &&
      !skullSurvivalRooms.empty()) {
    completed = true;
    return true;
  }
  return false;
}

bool SetFight::complete(GoalTypes goal, size_t count) {
  (void)goal;
  (void)count;
  return completed;
}

void SetFight::recordSkeletonKill(IdSector sector) {
  if (completed)
    return;
  skeletonSectors.insert(sector);
  checkComplete();
}

void SetFight::recordVampireKill(void *enemyPtr) {
  if (completed)
    return;
  Vampire *vampire = static_cast<Vampire *>(enemyPtr);
  if (!vampire || !vampire->isDead())
    return;
  Vampire *partner = vampire->getPartner();
  if (!partner || !partner->isDead())
    return;
  const Vampire *key = (vampire->getEnemyType() == EnemyType::VAMPIRE_MALE)
                           ? vampire
                           : partner;
  completedVampirePairs.insert(key);
  checkComplete();
}

void SetFight::recordOrcKill(int groupId) {
  if (completed)
    return;
  orcGroupKills[groupId]++;
  checkComplete();
}

void SetFight::recordSkullSurvival(IdSector sector) {
  if (completed)
    return;
  skullSurvivalRooms.insert(sector);
  checkComplete();
}

SetState SetFight::state() const {
  SetState result;
  result.type = static_cast<int>(SetType::FIGHT);
  result.completed = completed;
  result.goals.push_back({static_cast<int>(EnemyType::SKELETON),
                         static_cast<size_t>(consecutiveSkeletonCount()),
                         SET_FIGHT_COUNT_SKELETON});
  result.goals.push_back({static_cast<int>(EnemyType::VAMPIRE_MALE),
                         static_cast<size_t>(completedVampireCount()),
                         SET_FIGHT_COUNT_VAMPIRE});
  result.goals.push_back({static_cast<int>(EnemyType::ORC),
                         static_cast<size_t>(bestOrcGroupCount()),
                         SET_FIGHT_COUNT_ORC});
  result.goals.push_back({static_cast<int>(EnemyType::SKULL_BLUE),
                         skullSurvivalRooms.empty() ? 0u : 1u,
                         SET_FIGHT_COUNT_SKULL});
  return result;
}