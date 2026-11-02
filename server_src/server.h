#ifndef SERVER_H_
#define SERVER_H_

#include "./game/command.h"
#include "acceptor.h"
#include "gameloop.h"

class Server {
private:
  Lobby lobby;
  Acceptor acceptor;

public:
  explicit Server(const char *servname);

  void run();
};

#endif // SERVER_H_
