#include "gift_offer_action.h"
#include "../client_protocol.h"

GiftOfferAction::GiftOfferAction(const GiftOfferDto &dto) : dto(dto) {}

void GiftOfferAction::send_by(ClientProtocol &protocol) const {
  protocol.send_gift_offer_dto(dto);
}