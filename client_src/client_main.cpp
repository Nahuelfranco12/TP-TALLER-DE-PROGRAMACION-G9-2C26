#include <cstdlib>
#include <iostream>

#include "client.h"
#include "../common_src/constants.h"

int main(int argc, char* argv[]) {
    try {
        Client client(argv[1], argv[2]);
        client.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << STRING_BRK;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << UNKNOWN_OP_ERROR << STRING_BRK;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
