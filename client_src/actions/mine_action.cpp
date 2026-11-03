#include "mine_action.h"

MineAction::MineAction(DirectionDto direction) : dto{direction} {}

void MineAction::send_by(ClientProtocol &protocol) const {
  protocol.send_mine_dto(dto);
}
