#ifndef SET_FIGHT_H_
#define SET_FIGHT_H_

#include "server_src/game/game_constants.h"
#include "server_src/game/sets/set.h"

#include <cstddef>
#include <map>
#include <set>
#include <vector>

class SetFight : public Set {
private:
  std::set<IdSector> skeletonSectors;
  std::set<const void *> completedVampirePairs;
  std::map<int, int> orcGroupKills;
  std::set<IdSector> skullSurvivalRooms;

  bool completed = false;
  bool rewardApplied = false;

  size_t consecutiveSkeletonCount() const;
  size_t completedVampireCount() const;
  size_t bestOrcGroupCount() const;

  bool checkComplete();

public:
  SetFight();

  bool complete(GoalTypes goal, size_t count) override;
  bool isComplete() const override { return completed; }
  bool isRewardApplied() const { return rewardApplied; }
  void markRewardApplied() { rewardApplied = true; }

  SetType type() const override { return SetType::FIGHT; }
  SetState state() const override;

  void recordSkeletonKill(IdSector sector);
  void recordVampireKill(void *enemy);
  void recordOrcKill(int groupId);
  void recordSkullSurvival(IdSector sector);
};

#endif // SET_FIGHT_H_