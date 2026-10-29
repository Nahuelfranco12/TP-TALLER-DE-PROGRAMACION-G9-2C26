#ifndef CLIENT_QUEUES_H_
#define CLIENT_QUEUES_H_

#include <map>
#include <mutex>

#include "../common_src/queue.h"
#include "../common_src/game_dtos.h"

class ClientQueues {
    private:
        std::mutex mutex;
        std::map<int, Queue<WorldStateDto>*> queues;

    public:
        void add_client(int client_id, Queue<WorldStateDto>& queue);
        void remove_client(int client_id);
        void send_to_all(const WorldStateDto& state);
        int size();

};

#endif