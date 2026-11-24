#include "interact_action.h"
#include "../client_protocol.h"

InteractAction::InteractAction(const GamePositionDto &target) : dto{target} {}

void InteractAction::send_by(ClientProtocol &protocol) const {
  protocol.send_interact_dto(dto);
}