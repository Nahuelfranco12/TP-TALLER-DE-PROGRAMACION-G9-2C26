#include "redeem_set_command.h"

#include "../entities/player.h"
#include "../game_constants.h"
#include "../inventory/crop_item.h"
#include "../inventory/inventory.h"
#include "../sets/set.h"
#include "../world.h"

void RedeemSetCommand::execute(World &world) {
  Player *player = world.getPlayer(this->playerId);
  if (!player || this->amount <= 0)
    return;

  SetType setType = static_cast<SetType>(this->setIndex);
  if (setType == SetType::FIGHT)
    return; // solo se completa con acciones

  Set *targetSet = nullptr;
  for (const auto &set : world.getSets()) {
    if (set->type() == setType) {
      targetSet = set.get();
      break;
    }
  }
  if (!targetSet || targetSet->isComplete())
    return;

  Inventory &inventory = player->getInventory();

  if (setType == SetType::MONEY) {
    if (static_cast<int>(player->getCoins()) < this->amount)
      return;
    player->setCoins(static_cast<int>(player->getCoins()) - this->amount);
    world.recordProgress(GoalTypes(MoneyType::GOLD), this->amount);
    return;
  }

  if (this->slotIndex < 0 ||
      static_cast<size_t>(this->slotIndex) >= inventory.state().items.size())
    return;

  const Item *item = inventory.itemAt(this->slotIndex);
  if (!item || inventory.countAt(this->slotIndex) < static_cast<size_t>(this->amount))
    return;

  GoalTypes goal = GoalTypes(MineralTypes::GOLD);
  bool valid = false;

  switch (setType) {
  case SetType::CROP: {
    if (item->getType() != ItemType::CROP)
      return;
    const CropItem *cropItem = dynamic_cast<const CropItem *>(item);
    if (!cropItem)
      return;
    CropQuality quality = cropItem->getQuality();
    if (quality != CropQuality::INCREDIBLE && quality != CropQuality::PERFECT)
      return;
    goal = GoalTypes(static_cast<CropTypes>(item->subtypeToInt()));
    valid = true;
    break;
  }
  case SetType::METAL: {
    if (item->getType() != ItemType::MINERAL)
      return;
    goal = GoalTypes(static_cast<MineralTypes>(item->subtypeToInt()));
    valid = true;
    break;
  }
  case SetType::ANIMAL: {
    if (item->getType() != ItemType::ANIMAL_PRODUCT)
      return;
    goal = GoalTypes(static_cast<AnimalType>(item->subtypeToInt()));
    valid = true;
    break;
  }
  default:
    return;
  }

  if (!valid)
    return;

  for (int i = 0; i < this->amount; ++i) {
    if (!inventory.removeFromSlot(this->slotIndex))
      return;
  }

  world.recordProgress(goal, this->amount);
}