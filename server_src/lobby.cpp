#include "lobby.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <toml++/toml.hpp>

Lobby::Lobby(const std::filesystem::path &maps_directory)
    : maps(load_maps(maps_directory)) {}

std::vector<MapInfoDto>
Lobby::load_maps(const std::filesystem::path &maps_directory) {
  std::vector<MapInfoDto> maps;
  std::error_code error;
  std::filesystem::directory_iterator entries(maps_directory, error);
  if (error) {
    std::cerr << "No se pudo leer la carpeta de mapas '"
              << maps_directory.string() << "': " << error.message() << '\n';
    return maps;
  }

  for (const auto &entry : entries) {
    if (!entry.is_regular_file(error) || entry.path().extension() != ".toml")
      continue;

    try {
      toml::table document = toml::parse_file(entry.path().string());
      std::optional<std::string> name =
          document["nombre"].value<std::string>();
      if (!name || name->empty())
        throw std::runtime_error("falta el campo nombre");

      maps.push_back(MapInfoDto{*name,
                                (std::filesystem::path("maps") /
                                 entry.path().filename())
                                    .generic_string()});
    } catch (const std::exception &exception) {
      std::cerr << "Se omite el mapa '" << entry.path().string()
                << "': " << exception.what() << '\n';
    }
  }

  std::sort(maps.begin(), maps.end(),
            [](const MapInfoDto &left, const MapInfoDto &right) {
              return left.path < right.path;
            });
  return maps;
}

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

std::vector<MapInfoDto> Lobby::list_maps() {
  std::lock_guard<std::mutex> lock(mutex);
  return maps;
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
