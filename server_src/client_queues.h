#ifndef CLIENT_QUEUES_H
#define CLIENT_QUEUES_H_

#include <map>
#include <mutex>
#include <string>

#include "../common_src/queue.h"

class ClientQueues {
    private:
        std::mutex mutex;
        std::map<int, Queue<std::string>*> queues>;

    public:
        void add_client(int client_id, Queue<std::string>& queue);
        void remove_client(int client_id);
        void send_to_all(const std::string& msg);

}

#endif