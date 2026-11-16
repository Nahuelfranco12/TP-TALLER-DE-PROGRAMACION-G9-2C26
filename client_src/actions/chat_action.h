#ifndef CHAT_ACTION_H
#define CHAT_ACTION_H

#include <string>

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class ChatAction : public ClientAction {
private:
  ChatDto dto;

public:
  explicit ChatAction(const std::string &text);
  void send_by(ClientProtocol &protocol) const override;
};

#endif