#include "App.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace Zenith::Core;

int main() {
    App app{};

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}