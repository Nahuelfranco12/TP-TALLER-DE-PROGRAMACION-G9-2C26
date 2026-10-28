#include <iostream>

#include "client.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <host> <puerto>" << std::endl;
        return 1;
    }
    try {
        Client client(argv[1], argv[2]);
        client.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}