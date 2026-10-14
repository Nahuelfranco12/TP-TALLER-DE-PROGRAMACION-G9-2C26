#include <cstdlib>
#include <iostream>

#include "../common_src/constants.h"
#include "server.h"

int main(int argc, char* argv[]) {

    try {
        Server server(argv[1]);
        server.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << STRING_BRK;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << UNKNOWN_OP_ERROR << STRING_BRK;
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
