#ifndef DTOS_H_
#define DTOS_H_

#include <vector>
#include <string>

enum class Direction { Up, Down, Left, Right};

struct MoveCommand {
    Direction direction = Direction::Up;
};

struct PlayerPosition {
    int id = 0;
    int x = 0;
    int y = 0;
};

struct WorldState {
    std::vector<PlayerPosition> players;
};

struct MatchInfo {
    std::string code;
    std::string name;
    int players = 0;
};

enum class LobbyAction { Create, List, Join };

struct LobbyRequest {
    LobbyAction action = LobbyAction::List;
    std::string text;
};

#endif