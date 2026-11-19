#ifndef LOBBY_H
#define LOBBY_H

#include <map>
#include <memory>
#include <mutex>
#include <filesystem>
#include <random>
#include <string>
#include <vector>

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"

#include "match.h"

class Lobby {
private:
  std::mutex mutex;
  std::map<std::string, std::unique_ptr<Match>> matches;
  std::vector<MapInfoDto> maps;
  std::mt19937 rng{std::random_device{}()};
  std::string generate_code();
  static std::vector<MapInfoDto>
  load_maps(const std::filesystem::path &maps_directory);

public:
  explicit Lobby(const std::filesystem::path &maps_directory = "maps");

  std::string create_match(const std::string &name);
  std::vector<MatchInfoDto> list_matches();
  std::vector<MapInfoDto> list_maps();
  Match *find_match(const std::string &code);
};

#endif
