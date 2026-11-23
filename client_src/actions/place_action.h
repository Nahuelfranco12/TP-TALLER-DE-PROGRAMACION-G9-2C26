#ifndef PLACE_ACTION_H
#define PLACE_ACTION_H

#include "client_action.h"
#include "../../common_src/game_dtos.h"

class PlaceAction : public ClientAction {
private:
  PlaceDto dto;

public:
  PlaceAction(int slotIndex, DirectionDto direction);
  void send_by(ClientProtocol &protocol) const override;
};

#endif