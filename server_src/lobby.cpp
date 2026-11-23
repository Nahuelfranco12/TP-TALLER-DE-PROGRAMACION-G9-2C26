#include "lobby.h"

#include <memory>
#include <string>

std::string Lobby::create_match(const std::string &name) {
  std::lock_guard<std::mutex> lock(mutex);
  std::string code = generate_code();
  matches[code] = std::make_unique<Match>(name);
  return code;
}
std::vector<MatchInfoDto> Lobby::list_matches() {
  std::lock_guard<std::mutex> lock(mutex);
  std::vector<MatchInfoDto> matches_info;
  for (const auto &[code, match] : matches) {
    matches_info.push_back(
        MatchInfoDto{code, match->get_name(), match->player_count()});
  }
  return matches_info;
}
Match *Lobby::find_match(const std::string &code) {
  std::lock_guard<std::mutex> lock(mutex);
  auto map_iterator = matches.find(code);
  if (map_iterator == matches.end())
    return nullptr;
  return map_iterator->second.get();
}

std::string Lobby::generate_code() {
  static constexpr char LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::uniform_int_distribution<int> letter(0, 25);
  std::uniform_int_distribution<int> digit(0, 9);
  while (true) {
    std::string code;
    for (int i = 0; i < 4; ++i)
      code += LETTERS[letter(rng)];
    for (int i = 0; i < 2; ++i)
      code += static_cast<char>('0' + digit(rng));
    if (matches.count(code) == 0)
      return code;
  }
}
