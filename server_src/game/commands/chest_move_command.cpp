#include "chest_move_command.h"

#include "../entities/chest.h"
#include "../world.h"

void ChestMoveCommand::execute(World &world) {
  Player *player = world.getPlayer(playerId);
  if (!player)
    return;

  Chest *chest = player->getActualSector()->findChestOpenedBy(playerId);
  if (!chest)
    return;

  Inventory &from = toChest ? player->getInventory() : chest->getInventory();
  Inventory &to = toChest ? chest->getInventory() : player->getInventory();
  from.giveSlotTo(slotIndex, to);
}