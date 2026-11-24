#ifndef INTERACT_ACTION_H
#define INTERACT_ACTION_H

#include "client_action.h"
#include "../../common_src/game_dtos.h"

class InteractAction : public ClientAction {
private:
  InteractDto dto;

public:
  explicit InteractAction(const GamePositionDto &target);
  void send_by(ClientProtocol &protocol) const override;
};

#endif