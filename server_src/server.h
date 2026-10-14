#ifndef SERVER_H_
#define SERVER_H_

#include "acceptor.h"

class Server {
private:
    const char* servname;
    Acceptor acceptor;

public:
    Server(const char* servname);

    void run();
};

#endif  // SERVER_H_
