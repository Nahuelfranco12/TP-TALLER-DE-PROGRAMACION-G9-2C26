#include "lobby.h"

std::string Lobby::create_match(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex);
    std::string code = std::to_string(next_code++);
    matches[code] = std::make_unique<Match>(name);
    return code;
}
std::vector<MatchInfo> Lobby::list_matches() {
    std::lock_guard<std::mutex> lock(mutex);
    std::vector<MatchInfo> matches_info;
    for(const auto& [code, match] : matches) {
        matches_info.push_back(MatchInfo{code, match->get_name(), match->player_count()});
    }
    return matches_info;

}
Match* Lobby::join_match(const std::string& code, int client_id, Queue<WorldState>& to_send_queue) {
    std::lock_guard<std::mutex> lock(mutex);
    auto map_iterator = matches.find(code);
    if(map_iterator == matches.end())
        return nullptr;
    map_iterator->second->join(client_id, to_send_queue);
    return map_iterator->second.get();
}