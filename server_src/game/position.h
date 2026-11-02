#ifndef POSITION_H_
#define POSITION_H_

#include <cstddef>

class Position {
public:
  size_t x;
  size_t y;

  Position(size_t x, size_t y) : x(x), y(y) {}

    bool operator<(const Position& other) const {
        if (x != other.x) 
            return x < other.x;
        return y < other.y;
    }

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

  bool isAdjacentTo(const Position &other) const {
    size_t dx = (x > other.x) ? x - other.x : other.x - x;
    size_t dy = (y > other.y) ? y - other.y : other.y - y;
    return (dx + dy) == 1;
  }
};

#endif // POSITION_H_
