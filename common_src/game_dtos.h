#ifndef DTOS_H_
#define DTOS_H_

#include <vector>

enum class Direction { Up, Down, Left, Right};

struct MoveCommand {
    Direction direction = Direction::Up;
};

struct PlayerPosition {
    int id = 0;
    int x = 0;
    int y = 0;
}

struct WorldState {
    std::vector<PlayerPosition> players;
}

#endif