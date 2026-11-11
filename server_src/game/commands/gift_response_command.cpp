#include "gift_response_command.h"
#include "../world.h"

void GiftResponseCommand::execute(World &world) {
    Player *receiver = world.getPlayer(receiverId);
    if (!receiver || !receiver->hasPendingGift()) return;

    PendingGift gift = receiver->getPendingGift();
    receiver->clearPendingGift();
    if (!accept) return;

    Player *giver = world.getPlayer(gift.giverId);
    if (!giver) return;

    InventoryState inventory = giver->getInventory().state();
    if (gift.slotIndex >= static_cast<int>(inventory.items.size())) 
        return;
    const ItemState &now = inventory.items[gift.slotIndex];
    if (now.type != gift.item.type || now.subtype != gift.item.subtype || now.quality != gift.item.quality || now.count != gift.item.count) 
        return; 

    // TODO: revisar el chequeo de arriba a ver si funca para que no se envie mal el regalo
    giver->getInventory().giveSlotTo(gift.slotIndex, receiver->getInventory());
}