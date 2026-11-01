#include "client_sender.h"

#include <stdexcept>

ClientSender::ClientSender(ClientProtocol& protocol, Queue<std::unique_ptr<ClientAction>>& to_send_queue):
    protocol(protocol), to_send_queue(to_send_queue) {}

void ClientSender::run() {
    try {
        while(should_keep_running()) {
            std::unique_ptr<ClientAction> action = to_send_queue.pop();
            action->send_by(protocol);
        }
    } catch (const ClosedQueue&) {

    } catch (const std::exception&) {

    }

  protocol.shutdown();
}
