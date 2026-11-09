#include "till_action.h"

TillAction::TillAction(DirectionDto direction) : dto{direction} {}

void TillAction::send_by(ClientProtocol &protocol) const {
  protocol.send_till_dto(dto);
}
