#ifndef GIFT_RESPONSE_ACTION_H
#define GIFT_RESPONSE_ACTION_H

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class GiftResponseAction : public ClientAction {
private:
  GiftResponseDto dto;

public:
  explicit GiftResponseAction(bool accept);
  void send_by(ClientProtocol &protocol) const override;
};

#endif