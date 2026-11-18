#ifndef CHEAT_END_DAY_ACTION_H_
#define CHEAT_END_DAY_ACTION_H_

#include "client_action.h"

class CheatEndDayAction : public ClientAction {
public:
  CheatEndDayAction();

  void send_by(ClientProtocol &protocol) const override;
};

#endif
