#ifndef CHEAT_ENEMIES_DAMAGE_ACTION_H_
#define CHEAT_ENEMIES_DAMAGE_ACTION_H_

#include "client_action.h"

class CheatEnemiesDamageAction : public ClientAction {
public:
  CheatEnemiesDamageAction();

  void send_by(ClientProtocol &protocol) const override;
};

#endif
