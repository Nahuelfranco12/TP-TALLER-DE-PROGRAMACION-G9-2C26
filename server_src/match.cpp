#include "match.h"

#include <memory>
#include <utility>

#include "../common_src/constants.h"
#include "game/game_constants.h"

Match::Match(const std::string &name)
    : name(name), received_queue(QUEUE_MAX_SIZE),
      gameloop(received_queue, clients, DaySpeed::MEDIUM) {
  gameloop.start();
}

void Match::join(int client_id, Queue<WorldState> &to_send_queue,
                 std::unique_ptr<Command> join_cmd) {
  clients.add_client(client_id, to_send_queue);
  received_queue.push(std::move(join_cmd));
}

void Match::leave(int client_id) {
  clients.remove_client(client_id);
  try {
    received_queue.push(std::make_unique<LeaveCommand>(client_id));
  } catch (const ClosedQueue &) {
  }
}

void Match::push_command(std::unique_ptr<Command> cmd) {
  received_queue.push(std::move(cmd));
}

const std::string &Match::get_name() const { return name; }

int Match::player_count() { return clients.size(); }

Match::~Match() {
  // cppcheck-suppress throwInNoexceptFunction
  received_queue.close();
  gameloop.stop();
  gameloop.join();
}
