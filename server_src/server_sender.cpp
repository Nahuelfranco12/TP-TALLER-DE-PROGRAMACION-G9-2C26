#include "server_sender.h"

#include <optional>
#include <stdexcept>

ServerSender::ServerSender(ServerProtocol &protocol,
                           Queue<WorldState> &to_send_queue, int client_id)
    : protocol(protocol), to_send_queue(to_send_queue), client_id(client_id) {}

void ServerSender::run() {
  try {
    bool first_run = true;
    while (should_keep_running()) {
      WorldState state = to_send_queue.pop();
      if (first_run) {
        std::optional<SectorStateDto> farmSectorState = builder.buildSectorMap(state, SectorTypeDto::FARM);
        std::optional<SectorStateDto> cavernSectorState = builder.buildSectorMap(state, SectorTypeDto::CAVERN);
        std::optional<SectorStateDto> villageSectorState = builder.buildSectorMap(state, SectorTypeDto::VILLAGE);

        if (farmSectorState && cavernSectorState && villageSectorState)
          protocol.send_world_map_state(farmSectorState.value(), cavernSectorState.value(), villageSectorState.value());

        first_run = false;
      }
      std::optional<SectorStateDto> dto =
          builder.build(state, client_id);
      if (dto) {
        protocol.send_sector_state(dto.value(), true);
      }
    }
  } catch (const ClosedQueue &) {

  } catch (const std::exception &) {
  }

  protocol.shutdown();
}
