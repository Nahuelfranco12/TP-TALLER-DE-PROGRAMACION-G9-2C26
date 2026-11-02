#include "client_receiver.h"

#include <iostream>
#include <stdexcept>

#include "../common_src/constants.h"

ClientReceiver::ClientReceiver(ClientProtocol &protocol,
                               Queue<SectorStateDto> &received_queue)
    : protocol(protocol), received_queue(received_queue) {}

void ClientReceiver::run() {
  try {
    while (should_keep_running()) {
      SectorStateDto state = protocol.receive_sector_state();
      received_queue.try_push(state);
    }
  } catch (const ClosedQueue &) {

  } catch (const std::exception &) {
  }
}
