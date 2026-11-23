#include "place_action.h"
#include "../client_protocol.h"

PlaceAction::PlaceAction(int slotIndex, DirectionDto direction)
    : dto{slotIndex, direction} {}

void PlaceAction::send_by(ClientProtocol &protocol) const {
  protocol.send_place_dto(dto);
}