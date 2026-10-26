#ifndef POSITION_H_
#define POSITION_H_

#include <cstddef>

class Position {
public:
    size_t x;
    size_t y;

    Position(size_t x, size_t y) : x(x), y(y) {};

    bool operator<(const Position& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

#endif // POSITION_H_
