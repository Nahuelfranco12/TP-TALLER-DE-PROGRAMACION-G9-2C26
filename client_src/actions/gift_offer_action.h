#ifndef GIFT_OFFER_ACTION_H
#define GIFT_OFFER_ACTION_H

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class GiftOfferAction : public ClientAction {
private:
  GiftOfferDto dto;

public:
  explicit GiftOfferAction(const GiftOfferDto &dto);
  void send_by(ClientProtocol &protocol) const override;
};

#endif