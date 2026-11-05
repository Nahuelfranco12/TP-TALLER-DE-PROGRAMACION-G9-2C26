#include "collect_action.h"

CollectAction::CollectAction(DirectionDto direction) : dto{direction} {}

void CollectAction::send_by(ClientProtocol &protocol) const {
  protocol.send_collect_dto(dto);
}
