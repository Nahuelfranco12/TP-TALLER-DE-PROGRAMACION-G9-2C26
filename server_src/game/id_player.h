#ifndef ID_PLAYER_H_
#define ID_PLAYER_H_

#include <cstddef>
#include <limits>

typedef size_t IdPlayer;
static constexpr IdPlayer INVALID_PLAYER_ID = std::numeric_limits<size_t>::max();

#endif // ID_PLAYER_H_
