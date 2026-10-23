#ifndef CLIENT_HANDLER_H_
#define CLIENT_HANDLER_H_

#include <functional>
#include <map>
#include <string>

#include "server_sender.h"
#include "server_receiver.h"
#include "client_queues.h"
#include "../common_src/queue.h"
#include "../common_src/socket.h"
#include "../common_src/thread.h"

#include "server_protocol.h"

class ClientHandler {
private:
    int client_id;
    ServerProtocol protocol;
    Queue<WorldState> to_send_queue;
    Queue<ClientCommand>& received_queue;
    ClientQueues& clients;
    ServerReceiver receiver;
    ServerSender sender;
public:
    ClientHandler(Socket&& skt, int client_id, Queue<ClientCommand>& received_queue, ClientQueues& clients);

    void start();

    bool is_dead();

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

    ~ClientHandler();
};

#endif  // CLIENT_HANDLER_H_
