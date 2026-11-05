#ifndef COLLECT_ACTION_H_
#define COLLECT_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class CollectAction : public ClientAction {
private:
  CollectDto dto;

public:
  explicit CollectAction(DirectionDto direction);

  void send_by(ClientProtocol &protocol) const override;
};

#endif
