#include "gift_offer_command.h"
#include "../world.h"

void GiftOfferCommand::execute(World &world) {
  Player *giver = world.getPlayer(giverId);
  Player *receiver = world.getPlayer(receiverId);
  if (!giver || !receiver || giver == receiver)
    return;
  if (giver->getActualSector() != receiver->getActualSector())
    return;
  if (!giver->position.isAdjacentTo(receiver->position))
    return;
  if (receiver->hasPendingGift())
    return;

  InventoryState inventory = giver->getInventory().state();
  if (slotIndex < 0 || slotIndex >= static_cast<int>(inventory.items.size()))
    return;

  receiver->setPendingGift(
      PendingGift{giverId, slotIndex, inventory.items[slotIndex]});
}