#ifndef PLANT_COMMAND_H_
#define PLANT_COMMAND_H_

#include "../command.h"
#include "../game_constants.h"
#include "../position.h"

class PlantCommand : public Command {
private:
    int playerId;
    Position target;
    CropTypes crop;

public:
    PlantCommand(int playerId, Position target, CropTypes crop)
        : playerId(playerId), target(target), crop(crop) {}

    void execute(World &world) override;
};

#endif  // PLANT_COMMAND_H_