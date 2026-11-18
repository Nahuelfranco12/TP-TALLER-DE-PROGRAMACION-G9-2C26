#include "cheat_end_day_action.h"

CheatEndDayAction::CheatEndDayAction() {}

void CheatEndDayAction::send_by(ClientProtocol &protocol) const {
  protocol.send_end_day_cheat();
}