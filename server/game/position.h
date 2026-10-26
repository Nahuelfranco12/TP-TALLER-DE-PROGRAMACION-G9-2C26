#ifndef POSITION_H_
#define POSITION_H_

#include <cstddef>

class Position {
public:
    const size_t x;
    const size_t y;

    Position(size_t x, size_t y) : x(x), y(y) {};
};

#endif // POSITION_H_
