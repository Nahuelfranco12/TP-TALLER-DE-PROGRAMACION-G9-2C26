#include "plant_action.h"

PlantAction::PlantAction(int x, int y, CropTypeDto crop) {
    dto.target.x = x;
    dto.target.y = y;
    dto.crop = crop;
}

void PlantAction::send_by(ClientProtocol &protocol) const {
    protocol.send_plant_dto(dto);
}