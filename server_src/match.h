#ifndef MATCH_H
#define MATCH_H

#include <string>
#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"

#include "client_command.h"
#include "client_queues.h"
#include "gameloop.h"

class Match {
    private:
        std::string name;
        Queue<ClientCommand> received_queue;
        ClientQueues clients;
        Gameloop gameloop;
    
    public:
        explicit Match(const std::string& name);

        void join(int client_id, Queue<WorldState>& to_send_queue);
        void leave(int client_id);
        void send_command(const ClientCommand& cmd);
        const std::string& get_name() const;

        Match(const Match&) = delete;
        Match& operator=(const Match&) = delete;

        ~Match();

};

#endif