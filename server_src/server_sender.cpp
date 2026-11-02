#include "server_sender.h"

#include <optional>
#include <stdexcept>

ServerSender::ServerSender(ServerProtocol &protocol,
                           Queue<WorldState> &to_send_queue, int client_id)
    : protocol(protocol), to_send_queue(to_send_queue), client_id(client_id) {}

void ServerSender::run() {
  try {
    while (should_keep_running()) {
      WorldState state = to_send_queue.pop();
      std::optional<SectorStateDto> dto =
          builder.build(state, client_id, nullptr);
      if (dto) {
        protocol.send_sector_state(dto.value());
      }
    }
  } catch (const ClosedQueue &) {

  } catch (const std::exception &) {
  }

  protocol.shutdown();
}
