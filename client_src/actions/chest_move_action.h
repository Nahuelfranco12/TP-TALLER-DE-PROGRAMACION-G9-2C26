#ifndef CHEST_MOVE_ACTION_H
#define CHEST_MOVE_ACTION_H

#include "client_action.h"
#include "../../common_src/game_dtos.h"

class ChestMoveAction : public ClientAction {
private:
  ChestMoveDto dto;

public:
  ChestMoveAction(int slotIndex, bool toChest);
  
  void send_by(ClientProtocol &protocol) const override;
};

#endif