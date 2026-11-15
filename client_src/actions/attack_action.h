#ifndef ATTACK_ACTION_H_
#define ATTACK_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class AttackAction : public ClientAction {
private:
  AttackDto dto;

public:
  explicit AttackAction(DirectionDto direction);

  void send_by(ClientProtocol &protocol) const override;
};

#endif
