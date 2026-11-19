#ifndef BED_H_
#define BED_H_

#include "entity.h"

class Bed : public Entity {
private:
    bool sleeping;

public:
    Bed(Position position) : Entity(position.x, position.y, EntityTypes::BED), sleeping(false) {}

    bool isSleeping() const { return this->sleeping; }
    bool sleep() {
        this->sleeping = !this->sleeping;
        return this->sleeping;
    }
    void setSleeping(bool value) { this->sleeping = value; }

    EntityState entityState() const override {
        EntityState state = Entity::entityState();
        state.bed.sleeping = sleeping;
        return state;
    }
};

#endif // BED_H_
