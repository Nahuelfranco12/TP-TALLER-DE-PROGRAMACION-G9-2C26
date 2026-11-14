#include "cheat_growth_action.h"

CheatGrowthAction::CheatGrowthAction() {}

void CheatGrowthAction::send_by(ClientProtocol &protocol) const {
  protocol.send_growth_cheat();
}
