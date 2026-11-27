#ifndef REDEEM_SET_ACTION_H
#define REDEEM_SET_ACTION_H

#include "client_action.h"
#include "../../common_src/game_dtos.h"

class RedeemSetAction : public ClientAction {
private:
  RedeemSetDto dto;

public:
  RedeemSetAction(int setIndex, int slotIndex, int amount);
  
  void send_by(ClientProtocol &protocol) const override;
};

#endif