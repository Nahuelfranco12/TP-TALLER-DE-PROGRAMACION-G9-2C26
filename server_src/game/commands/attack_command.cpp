#include "attack_command.h"

#include "../entities/enemies/enemy.h"
#include "../entities/enemies/orc.h"
#include "../sets/set_fight.h"
#include "../world.h"

void AttackCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player)
    return;

  // cppcheck-suppress constVariablePointer
  Sector *sector = player->getActualSector();
  if (!sector)
    return;

  Position targetPos(player->position.x, player->position.y);
  switch (this->direction) {
  case DirectionDto::Up:
    targetPos.y = player->position.y - 1;
    break;
  case DirectionDto::Down:
    targetPos.y = player->position.y + 1;
    break;
  case DirectionDto::Left:
    targetPos.x = player->position.x - 1;
    break;
  case DirectionDto::Right:
    targetPos.x = player->position.x + 1;
    break;
  }

  Entity *entity = sector->getEntity(targetPos);
  if (!entity)
    return;

  Enemy *enemy = dynamic_cast<Enemy *>(entity);
  if (!enemy)
    return;

  EnemyType enemyType = enemy->getEnemyType();
  IdSector sectorId = sector->getId();

  SetFight *fightSet = nullptr;
  for (const auto &set : world.getSets()) {
    if (set->type() == SetType::FIGHT) {
      fightSet = dynamic_cast<SetFight *>(set.get());
      break;
    }
  }

  bool wasComplete = fightSet ? fightSet->isComplete() : false;

  if (player->attack(*enemy)) {
    if (fightSet) {
      switch (enemyType) {
      case EnemyType::SKELETON:
        fightSet->recordSkeletonKill(sectorId);
        break;
      case EnemyType::VAMPIRE_MALE:
      case EnemyType::VAMPIRE_FEMALE:
        fightSet->recordVampireKill(enemy);
        break;
      case EnemyType::ORC: {
        Orc *orc = dynamic_cast<Orc *>(enemy);
        if (orc)
          fightSet->recordOrcKill(orc->getGroupId());
        break;
      }
      case EnemyType::SKULL_BLUE:
      case EnemyType::SKULL_GREEN:
        if (!player->tookDamageInCavern())
          fightSet->recordSkullSurvival(sectorId);
        break;
      default:
        break;
      }

      if (!wasComplete && fightSet->isComplete() && !fightSet->isRewardApplied()) {
        world.applySetReward(SetType::FIGHT);
        fightSet->markRewardApplied();
      }
    }
  }
}