#ifndef CHEAT_GROWTH_ACTION_H_
#define CHEAT_GROWTH_ACTION_H_

#include "client_action.h"

class CheatGrowthAction : public ClientAction {
public:
  explicit CheatGrowthAction();

  void send_by(ClientProtocol &protocol) const override;
};

#endif
