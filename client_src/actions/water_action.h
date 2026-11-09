#ifndef WATER_ACTION_H_
#define WATER_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class WaterAction : public ClientAction {
private:
  WaterDto dto;

public:
  explicit WaterAction(DirectionDto direction);

  void send_by(ClientProtocol &protocol) const override;
};

#endif
