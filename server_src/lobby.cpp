#include "lobby.h"

std::string Lobby::create_match(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex);
    std::string code = std::to_string(next_code++);
    matches[code] = std::make_unique<Match>(name);
    return code;
}
std::vector<MatchInfoDto> Lobby::list_matches() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<MatchInfoDto> matches_info;
    for(const auto& [code, match] : matches) {
        matches_info.push_back(MatchInfoDto{code, match->get_name(), match->player_count()});
    }
    return matches_info;

}
Match* Lobby::find_match(const std::string& code) {
    std::lock_guard<std::mutex> lock(mutex);
    auto map_iterator = matches.find(code);
    if(map_iterator == matches.end())
        return nullptr;
    return map_iterator->second.get();
}