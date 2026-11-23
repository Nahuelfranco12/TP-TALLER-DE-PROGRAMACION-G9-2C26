#ifndef MINE_ACTION_H_
#define MINE_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class MineAction : public ClientAction {
private:
  MineDto dto;

public:
  explicit MineAction(DirectionDto direction);

  void send_by(ClientProtocol &protocol) const override;
};

#endif
