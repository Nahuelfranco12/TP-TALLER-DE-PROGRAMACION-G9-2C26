#ifndef ENTITY_H_
#define ENTITY_H_

#include "../position.h"

class Entity {
public:
    Position position;

    Entity(size_t pos_x, size_t pos_y) : position(pos_x, pos_y) {};
    virtual ~Entity() = default;

    void setPosition(Position newPosition) { this->position = newPosition; }
};

#endif // ENTITY_H_
