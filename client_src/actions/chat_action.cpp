#include "chat_action.h"
#include "../client_protocol.h"

ChatAction::ChatAction(const std::string &text) : dto{text} {}

void ChatAction::send_by(ClientProtocol &protocol) const {
  protocol.send_chat_dto(dto);
}