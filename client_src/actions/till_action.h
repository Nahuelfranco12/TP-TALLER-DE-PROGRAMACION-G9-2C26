#ifndef TILL_ACTION_H_
#define TILL_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class TillAction : public ClientAction {
private:
  TillDto dto;

public:
  explicit TillAction(DirectionDto direction);

  void send_by(ClientProtocol &protocol) const override;
};

#endif
