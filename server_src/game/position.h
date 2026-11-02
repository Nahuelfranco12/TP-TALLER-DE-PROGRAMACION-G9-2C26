#ifndef POSITION_H_
#define POSITION_H_

#include <cstddef>

class Position {
public:
  int x;
  int y;

  Position(int x, int y) : x(x), y(y) {}

  bool operator<(const Position &other) const {
    if (x != other.x)
      return x < other.x;
    return y < other.y;
  }

  bool operator==(const Position &other) const {
    return x == other.x && y == other.y;
  }

  bool isAdjacentTo(const Position &other) const {
    int dx = (x > other.x) ? x - other.x : other.x - x;
    int dy = (y > other.y) ? y - other.y : other.y - y;
    return (dx + dy) == 1;
  }
};

#endif // POSITION_H_
