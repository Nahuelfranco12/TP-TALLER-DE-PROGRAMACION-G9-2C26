#ifndef LOBBY_H
#define LOBBY_H

#include <map>
#include <mutex>
#include <string>
#include <vector>

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"

#include "match.h"

class Lobby {
    private:
        std::mutex mutex;
        std::map<std::string, std::unique_ptr<Match>> matches;
        int next_code = 1;

    public:
        std::string create_match(const std::string& name);
        std::vector<MatchInfo> list_matches();
        Match* find_match(const std::string& code);
};

#endif