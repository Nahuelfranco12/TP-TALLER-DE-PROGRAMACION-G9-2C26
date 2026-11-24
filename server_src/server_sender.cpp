#include "server_sender.h"

#include <optional>
#include <stdexcept>

ServerSender::ServerSender(ServerProtocol &protocol,
                           Queue<WorldState> &to_send_queue, int client_id)
    : protocol(protocol), to_send_queue(to_send_queue), client_id(client_id) {}

void ServerSender::run() {
  try {
    bool map_sent = false;
    while (should_keep_running()) {
      WorldState state = to_send_queue.pop();
      WorldState newer_state;
      while (to_send_queue.try_pop(newer_state)) {
        newer_state.chat.insert(newer_state.chat.begin(), state.chat.begin(),
                                state.chat.end());
        state = std::move(newer_state);
      }
      std::optional<SectorStateDto> dto = builder.build(state, client_id);
      if (!dto) {
        continue;
      }

      if (!map_sent) {
        WorldMapDto map;
        for (SectorTypeDto type : {SectorTypeDto::FARM, SectorTypeDto::VILLAGE,
                                   SectorTypeDto::CAVERN, SectorTypeDto::COMMUNITY_CENTER}) {
          std::optional<SectorStateDto> sector =
              builder.buildSectorMap(state, type);
          if (sector) {
            map.sectors.push_back(sector.value());
          }
        }
        protocol.send_world_map(map);
        map_sent = true;
      }
      protocol.send_sector_state(dto.value());
    }
  } catch (const ClosedQueue &) {

  } catch (const std::exception &) {
  }

  protocol.shutdown();
}
