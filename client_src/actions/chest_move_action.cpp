#include "chest_move_action.h"
#include "../client_protocol.h"

ChestMoveAction::ChestMoveAction(int slotIndex, bool toChest)
    : dto{slotIndex, toChest} {}

void ChestMoveAction::send_by(ClientProtocol &protocol) const {
  protocol.send_chest_move_dto(dto);
}