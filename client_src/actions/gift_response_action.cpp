#include "gift_response_action.h"
#include "../client_protocol.h"

GiftResponseAction::GiftResponseAction(bool accept) : dto{accept} {}

void GiftResponseAction::send_by(ClientProtocol &protocol) const {
    protocol.send_gift_response_dto(dto);
}