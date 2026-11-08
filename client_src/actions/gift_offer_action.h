#ifndef GIFT_OFFER_ACTION_H
#define GIFT_OFFER_ACTION_H

#include "client_action.h"
#include "../../common_src/game_dtos.h"

class GiftOfferAction : public ClientAction {
private:
    GiftOfferDto dto;

public:
    explicit GiftOfferAction(const GiftOfferDto &dto);
    void send_by(ClientProtocol &protocol) const override;
};

#endif