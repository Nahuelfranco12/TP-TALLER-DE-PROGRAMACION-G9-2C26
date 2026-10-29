#ifndef MOVE_ACTION_H_
#define MOVE_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class MoveAction: public ClientAction {
private:
    MoveDto dto;

public:
    explicit MoveAction(Direction direction);
    void send_by(ClientProtocol& protocol) const override;
};

#endif