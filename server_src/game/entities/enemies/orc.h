#ifndef ORC_H_
#define ORC_H_

#include <cstdlib>
#include "enemy.h"
#include "../../inventory/mineral_item.h"

class Orc : public Enemy {
private:
  int groupId = -1;
public:
  Orc(size_t pos_x, size_t pos_y, EnemyStats orcStats)
      : Enemy(EnemyType::ORC, pos_x, pos_y, orcStats) {}

  std::unique_ptr<Item> dropItem() const override {
    if (std::rand() % 100 >= ORC_SILVER_DROP_PERCENT)
      return nullptr;
    return std::make_unique<MineralItem>(PRICE_IRON, MineralTypes::IRON);
  }

  bool removeOnDeath() const override { return true; }

  int getGroupId() const { return groupId; }
  void setGroupId(int id) { groupId = id; }

  void tick() override {
    Enemy::tick();
    if (!isDead())
      return;
  }
};

#endif // ORC_H_
