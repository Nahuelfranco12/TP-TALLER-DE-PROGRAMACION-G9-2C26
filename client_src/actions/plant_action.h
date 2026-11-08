#ifndef PLANT_ACTION_H_
#define PLANT_ACTION_H_

#include "../../common_src/game_dtos.h"
#include "client_action.h"

class PlantAction : public ClientAction {
private:
    PlantDto dto;

public:
    PlantAction(int x, int y, CropTypeDto crop);
    void send_by(ClientProtocol &protocol) const override;
};

#endif