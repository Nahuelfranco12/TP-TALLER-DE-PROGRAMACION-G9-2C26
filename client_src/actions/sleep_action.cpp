#include "sleep_action.h"

#include "../../common_src/constants.h"

void SleepAction::send_by(ClientProtocol &protocol) const {
  protocol.send_sleep();
}
