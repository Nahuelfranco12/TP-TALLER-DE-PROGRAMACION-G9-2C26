#include "cheat_enemies_damage_action.h"

CheatEnemiesDamageAction::CheatEnemiesDamageAction() {}

void CheatEnemiesDamageAction::send_by(ClientProtocol &protocol) const {
  protocol.send_enemies_damage_cheat();
}
