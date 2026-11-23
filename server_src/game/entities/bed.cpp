#include "bed.h"

#include "player.h"

void Bed::interact(World &, Player &player) {
  if (player.isSleeping()) {
    if (occupied) {
      player.wakeUp();
      occupied = false;
    }
    return;
  }

  if (!occupied) {
    occupied = true;
    player.goToSleep();
  }
}