#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <memory>

#include "../common_src/constants.h"
#include "../common_src/game_dtos.h"
#include "../common_src/queue.h"
#include "actions/client_action.h"
#include "client_receiver.h"
#include "client_sender.h"

class Client {
private:
    ClientProtocol protocol;
    int my_id;
    Queue<SectorStateDto> received_queue;
    Queue<std::unique_ptr<ClientAction>> to_send_queue;
    ClientReceiver receiver;
    ClientSender sender;
    bool in_game = false;

public:
  explicit Client(const char *hostname, const char *servname);

    void send_join();
    void send_move(DirectionDto direction);
    bool try_get_latest_state(SectorStateDto& state);
    bool is_connected() const;

    //Comandos para QT
    std::string create_match(const std::string& name);
    std::vector<MatchInfoDto> list_matches();
    bool join_match(const std::string& code);

  void run();

  ~Client();
};

#endif // CLIENT_H_
