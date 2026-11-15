#include "attack_action.h"

AttackAction::AttackAction(DirectionDto direction): dto{direction} {}

void AttackAction::send_by(ClientProtocol &protocol) const {
  protocol.send_attack_dto(dto);
}
