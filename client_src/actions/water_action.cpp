#include "water_action.h"

WaterAction::WaterAction(DirectionDto direction) : dto{direction} {}

void WaterAction::send_by(ClientProtocol &protocol) const {
  protocol.send_water_dto(dto);
}
