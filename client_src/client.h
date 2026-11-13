#ifndef CLIENT_H_
#define CLIENT_H_

#include <memory>
#include <string>
#include <vector>

#include "../common_src/constants.h"
#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "actions/client_action.h"
#include "client_receiver.h"
#include "client_sender.h"

class Client {
private:
  ClientProtocol protocol;
  int my_id;
  Queue<SectorStateDto> received_queue;
  Queue<std::unique_ptr<ClientAction>> to_send_queue;
  ClientReceiver receiver;
  ClientSender sender;
  bool in_game = false;
  WorldMapDto world_map;

public:
  explicit Client(const char *hostname, const char *servname);

  void send_join();
  void send_move(DirectionDto direction);
  void send_select_tool(ToolTypeDto tool);
  void send_mine(DirectionDto direction);
  void send_collect(DirectionDto direction);
  void send_plant(int x, int y, CropTypeDto crop);
  void send_gift_offer(int receiverId, int slotIndex);
  void send_gift_response(bool accept);
  void send_till(DirectionDto direction);
  void send_water(DirectionDto direction);
  void send_cheat_water(DirectionDto direction);

  bool try_get_latest_state(SectorStateDto &state);
  bool is_connected() const;
  int get_my_id() const;
  const WorldMapDto &get_world_map() const;

  // Comandos para QT
  std::string create_match(const std::string &name);
  std::vector<MatchInfoDto> list_matches();
  bool join_match(const std::string &code, const std::string &player_name,
                  const PlayerOutfitDto &outfit);

  void run();

  ~Client();
};

#endif // CLIENT_H_
