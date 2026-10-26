#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <map>

#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"

#include "client_command.h"
#include "client_queues.h"


#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define START_X 10
#define START_Y 10

#define TICKS_PER_SECOND 30

struct Position {
    int x;
    int y;
};

class Gameloop: public Thread {
    private:
        Queue<ClientCommand>& received_queue;
        ClientQueues& clients;
        std::map<int, Position> positions;

        void apply_cmd(const ClientCommand& cmd);
        void move(int client_id, Direction direction);
        WorldState make_world_state() const;
    public:
        Gameloop(Queue<ClientCommand>& received_queue, ClientQueues& clients);

        void run() override;
};

#endif