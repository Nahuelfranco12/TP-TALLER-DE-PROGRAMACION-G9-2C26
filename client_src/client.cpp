#include "client.h"

#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "../common_src/constants.h"
#include "actions/attack_action.h"
#include "actions/cheat_growth_action.h"
#include "actions/collect_action.h"
#include "actions/gift_offer_action.h"
#include "actions/gift_response_action.h"
#include "actions/mine_action.h"
#include "actions/move_action.h"
#include "actions/plant_action.h"
#include "actions/select_tool_action.h"
#include "actions/till_action.h"
#include "actions/water_action.h"

Client::Client(const char *hostname, const char *servname)
    : protocol(hostname, servname), my_id(protocol.receive_player_id()),
      received_queue(QUEUE_MAX_SIZE), to_send_queue(QUEUE_MAX_SIZE),
      receiver(protocol, received_queue), sender(protocol, to_send_queue) {}

// Métodos de acciones

void Client::send_move(DirectionDto direction) {
  to_send_queue.try_push(std::make_unique<MoveAction>(direction));
}

void Client::send_select_tool(ToolTypeDto tool) {
  to_send_queue.try_push(std::make_unique<SelectToolAction>(tool));
}

void Client::send_mine(DirectionDto direction) {
  to_send_queue.try_push(std::make_unique<MineAction>(direction));
}

void Client::send_collect(DirectionDto direction) {
  to_send_queue.try_push(std::make_unique<CollectAction>(direction));
}

void Client::send_plant(int x, int y, CropTypeDto crop) {
  to_send_queue.try_push(std::make_unique<PlantAction>(x, y, crop));
}

void Client::send_gift_offer(int receiverId, int slotIndex) {
  GiftOfferDto dto{.receiverId = receiverId, .slotIndex = slotIndex};
  to_send_queue.try_push(std::make_unique<GiftOfferAction>(dto));
}

void Client::send_gift_response(bool accept) {
  to_send_queue.try_push(std::make_unique<GiftResponseAction>(accept));
}
void Client::send_till(DirectionDto direction) {
  to_send_queue.try_push(std::make_unique<TillAction>(direction));
}

void Client::send_water(DirectionDto direction) {
  to_send_queue.try_push(std::make_unique<WaterAction>(direction));
}

void Client::send_attack(DirectionDto direction) {
  to_send_queue.try_push(std::make_unique<AttackAction>(direction));
}

void Client::send_cheat_water(DirectionDto direction) {
  to_send_queue.try_push(std::make_unique<WaterAction>(direction));
}

void Client::send_cheat_growth() {
  to_send_queue.try_push(std::make_unique<CheatGrowthAction>());
}

bool Client::try_get_latest_state(SectorStateDto &state) {
  bool has_been_received = false;
  SectorStateDto next_state;
  while (received_queue.try_pop(next_state)) {
    has_been_received = true;
  }

  if (has_been_received) {
    state = std::move(next_state);
  }
  return has_been_received;
}

bool Client::is_connected() const { return receiver.is_alive(); }

int Client::get_my_id() const { return my_id; }

Client::~Client() {
  receiver.stop();
  sender.stop();
  // cppcheck-suppress throwInNoexceptFunction
  to_send_queue.close();
  received_queue.close();
  protocol.shutdown();
  if (in_game) {
    receiver.join();
    sender.join();
  }
}

// Métodos de menú (QT)

std::string Client::create_match(const std::string &name) {
  protocol.send_create_match(name);
  return protocol.receive_created_match();
}

std::vector<MatchInfoDto> Client::list_matches() {
  protocol.send_list_matches();
  return protocol.receive_match_list();
}

bool Client::join_match(const std::string &code, const std::string &player_name,
                        const PlayerOutfitDto &outfit) {
  protocol.send_join_match(code, player_name, outfit);
  bool client_could_join = protocol.receive_join_result();
  if (client_could_join) {
    world_map = protocol.receive_world_map();
    receiver.start();
    sender.start();
    in_game = true;
  }
  return client_could_join;
}

const WorldMapDto &Client::get_world_map() const { return world_map; }
