#include "redeem_set_action.h"
#include "../client_protocol.h"

RedeemSetAction::RedeemSetAction(int setIndex, int slotIndex, int amount)
    : dto{setIndex, slotIndex, amount} {}

void RedeemSetAction::send_by(ClientProtocol &protocol) const {
  protocol.send_redeem_set_dto(dto);
}