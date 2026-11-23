#ifndef PLAYER_OUTFIT_H_
#define PLAYER_OUTFIT_H_

#include "../game_constants.h"

class PlayerOutfit {
public:
  PlayerHats hat;
  PlayerHairs hair;
  PlayerShirts tshirt;
  PlayerPants pants;

  PlayerOutfit(PlayerHats hat, PlayerHairs hair, PlayerShirts tshirt,
               PlayerPants pants)
      : hat(hat), hair(hair), tshirt(tshirt), pants(pants) {}
};

#endif // PLAYER_OUTFIT_H_
