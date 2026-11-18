#ifndef SLEEP_ACTION_H_
#define SLEEP_ACTION_H_

#include "client_action.h"

class SleepAction : public ClientAction {
public:
  void send_by(ClientProtocol &protocol) const override;
};

#endif // SLEEP_ACTION_H_
