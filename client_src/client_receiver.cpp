#include "client_receiver.h"

#include <iostream>
#include <stdexcept>

#include "../common_src/constants.h"

ClientReceiver::ClientReceiver(ClientProtocol &protocol,
                               Queue<SectorStateDto> &received_queue)
    : protocol(protocol), received_queue(received_queue) {}

void ClientReceiver::run() {
  try {
    bool first_run = true;
    while (should_keep_running()) {
      if (first_run) {
        SectorStateDto farmState = protocol.receive_sector_map_state();
        SectorStateDto cavernState = protocol.receive_sector_map_state();
        // SectorStateDto villageState = protocol.receive_sector_map_state();

        received_queue.try_push(farmState);
        received_queue.try_push(cavernState);
      }
      SectorStateDto state = protocol.receive_sector_state();
      received_queue.try_push(state);
    }
  } catch (const ClosedQueue &) {

  } catch (const std::exception &) {
  }
}
