#include "chest.h"

#include "player.h"

void Chest::interact(World &, Player &player) {
  if (openedBy == player.getId())
    openedBy = INVALID_PLAYER_ID;
  else if (openedBy == INVALID_PLAYER_ID)
    openedBy = player.getId();
}