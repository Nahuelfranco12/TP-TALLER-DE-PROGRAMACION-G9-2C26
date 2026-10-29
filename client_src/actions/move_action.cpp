#include "move_action.h"

MoveAction::MoveAction(Direction direction): dto{direction} {}

void MoveAction::send_by(ClientProtocol& protocol) const {
    protocol.send_move_dto(dto);
}